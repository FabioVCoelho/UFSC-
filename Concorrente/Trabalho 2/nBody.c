#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <mpi.h>

/*
 * pRNG based on http://www.cs.wm.edu/~va/software/park/park.html
 */
#define MODULUS    2147483647
#define MULTIPLIER 48271
#define DEFAULT    123456789

static long seed = DEFAULT;
double dt, dt_old; /* Alterado de static para global */

double Random(void)
/* ----------------------------------------------------------------
 * Random returns a pseudo-random real number uniformly distributed 
 * between 0.0 and 1.0. 
 * ----------------------------------------------------------------
 */
{
  const long Q = MODULUS / MULTIPLIER;
  const long R = MODULUS % MULTIPLIER;
        long t;

  t = MULTIPLIER * (seed % Q) - R * (seed / Q);
  if (t > 0) 
    seed = t;
  else 
    seed = t + MODULUS;
  return ((double) seed / MODULUS);
}

/*
 * End of the pRNG algorithm
 */

typedef struct {
    double x, y, z;
    double mass;
} Particle;

typedef struct {
    double xold, yold, zold;
    double fx, fy, fz;
} ParticleV;

void InitParticles( int, Particle[], ParticleV [], int );
double ComputeForces( Particle [], ParticleV [], int );
double ComputeNewPos( Particle [], ParticleV [], int, double);

int main(int argc, char **argv)
{
    MPI_Datatype Particle_type, ParticleV_type;
    Particle  * particles;   /* Particles */
    ParticleV * pv;          /* Particle velocity */
    int         base, nParticles, i, j, d;
    int         timesteps;         /* number of times in loop */
    double      sim_t;       /* Simulation time */
    int tmp;

    if(argc != 3){
		printf("Wrong number of parameters.\nUsage: nbody num_bodies timesteps\n");
		exit(1);
	}
    
	nParticles = atoi(argv[1]);
	timesteps = atoi(argv[2]);
	dt = 0.001; 
	dt_old = 0.001;

  /* Sending the Particles */

  MPI_Init(&argc, &argv); // inicializao ambiente MPI
    MPI_Datatype type1[4] = {MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE};
    MPI_Datatype type2[6] = {MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE};
    int blk_len[6] = {0,0,0,0,0,0};
    MPI_Aint disp[6];
    Particle part;
    ParticleV partV;

    MPI_Address( &part.x, disp);
    MPI_Address( &part.y, disp+1);
    MPI_Address( &part.z, disp+2);
    MPI_Address( &part.mass, disp+3);
    base = disp[0];
    for( i = 0; i < 4; i++ )
     disp[i] -= base;
    MPI_Type_struct( 4, blk_len, disp, type1, &Particle_type );
    MPI_Type_commit(&Particle_type);

    MPI_Address( &partV.xold, disp);
    MPI_Address( &partV.yold, disp+1);
    MPI_Address( &partV.zold, disp+2);
    MPI_Address( &partV.fx, disp+3);
    MPI_Address( &partV.fy, disp+4);
    MPI_Address( &partV.fz, disp+5);
    base = disp[0];
    for( i = 0; i < 6; i++ )
     disp[i] -= base;
    MPI_Type_struct( 6, blk_len, disp, type2, &ParticleV_type );
    MPI_Type_commit(&ParticleV_type);

    /* Allocate memory for particles */
    particles = (Particle *) malloc(sizeof(Particle)*nParticles);
    pv = (ParticleV *) malloc(sizeof(ParticleV)*nParticles);
    
  int size,rank;
  MPI_Status st;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  sim_t = 0.0;

  // MASTER
  if (rank == 0)  {
    for(i = 1; i < size; i++) {
      /*  Generate the initial values
          InitParticles( particles, pv, nParticles);
          Cada processo vai gerar a sua particula e enviar para o mestre. */
      int opcao = 0;
      if (i < nParticles + 1) {
        MPI_Send(&opcao,1,MPI_INT,i,0,MPI_COMM_WORLD);
      } else {
        MPI_Send(NULL,0,MPI_INT,i,0,MPI_COMM_WORLD);
      }
    }
    /*
     * Pode ser que um dia dê problema por causa da condição de corrida, verificar com o professor.
     */
    for(d = 1; d < size; d++) {
      if (d < nParticles + 1) {
        int i;
        double x,y,z,mass,xold,yold,zold,fx,fy,fz;
        MPI_Recv(&i,1,MPI_INT,d,MPI_ANY_TAG,MPI_COMM_WORLD,&st);
        MPI_Recv(&x,1,MPI_DOUBLE,d,MPI_ANY_TAG,MPI_COMM_WORLD,&st);
        particles[i].x = x;
        MPI_Recv(&y,1,MPI_DOUBLE,d,MPI_ANY_TAG,MPI_COMM_WORLD,&st);
        particles[i].y = y;
        MPI_Recv(&z,1,MPI_DOUBLE,d,MPI_ANY_TAG,MPI_COMM_WORLD,&st);
        particles[i].z = z;
        MPI_Recv(&mass,1,MPI_DOUBLE,d,MPI_ANY_TAG,MPI_COMM_WORLD,&st);
        particles[i].mass = mass;
        MPI_Recv(&xold,1,MPI_DOUBLE,d,MPI_ANY_TAG,MPI_COMM_WORLD,&st);
        pv[i].xold = xold;
        MPI_Recv(&yold,1,MPI_DOUBLE,d,MPI_ANY_TAG,MPI_COMM_WORLD,&st);
        pv[i].yold = yold;
        MPI_Recv(&zold,1,MPI_DOUBLE,d,MPI_ANY_TAG,MPI_COMM_WORLD,&st);
        pv[i].zold = zold;
        MPI_Recv(&fx,1,MPI_DOUBLE,d,MPI_ANY_TAG,MPI_COMM_WORLD,&st);
        pv[i].fx = fx;
        MPI_Recv(&fy,1,MPI_DOUBLE,d,MPI_ANY_TAG,MPI_COMM_WORLD,&st);
        pv[i].fy = fy;
        MPI_Recv(&fz,1,MPI_DOUBLE,d,MPI_ANY_TAG,MPI_COMM_WORLD,&st);
        pv[i].fz = fz;
      }
    }
    /* Aqui tem todas as particulas iniciadas e prontas para serem usadas =P */


  while (timesteps--) {
  double max_f;
  /* Compute forces (2D only) */
  int i;
  max_f = 0.0;
  for (i=0; i<nParticles; i++) {
    int j;
    double xi, yi, mi, rx, ry, mj, r, fx, fy, rmin;
    rmin = 100.0;
    xi   = particles[i].x;
    yi   = particles[i].y;
    fx   = 0.0;
    fy   = 0.0;
    for (j=0; j<nParticles; j++) {
      rx = xi - particles[j].x;
      ry = yi - particles[j].y;
      mj = particles[j].mass;
      r  = rx * rx + ry * ry;
      /* ignore overlap and same particle */
      if (r == 0.0) continue;
      if (r < rmin) rmin = r;
      r  = r * sqrt(r);
      fx -= mj * rx / r;
      fy -= mj * ry / r;
    }
    pv[i].fx += fx;
    pv[i].fy += fy;
    fx = sqrt(fx*fx + fy*fy)/rmin;
    if (fx > max_f) max_f = fx;
  }

  /* Once we have the forces, we compute the changes in position */
  sim_t += ComputeNewPos( particles, pv, nParticles, max_f);
  }
  for (i=0; i<nParticles; i++)
    fprintf(stdout,"%.5lf %.5lf\n", particles[i].x, particles[i].y);
  




  } //SLAVE
   else {
    int opcao;
    MPI_Recv(&opcao,1,MPI_INT,0,MPI_ANY_TAG,MPI_COMM_WORLD,&st);
    if (opcao == 0) {
      int i = rank - 1;
      seed = seed*rank;
      particles[i].x    = Random();
      particles[i].y    = Random();
      particles[i].z    = Random();
      particles[i].mass = 1.0;
      pv[i].xold    = particles[i].x;
      pv[i].yold    = particles[i].y;
      pv[i].zold    = particles[i].z;
      pv[i].fx    = 0;
      pv[i].fy    = 0;
      pv[i].fz    = 0;

      MPI_Send(&i,1,MPI_INT,0,0,MPI_COMM_WORLD);
      MPI_Send(&particles[i].x,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
      MPI_Send(&particles[i].y,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
      MPI_Send(&particles[i].z,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
      MPI_Send(&particles[i].mass,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
      MPI_Send(&pv[i].xold,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
      MPI_Send(&pv[i].yold,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
      MPI_Send(&pv[i].zold,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
      MPI_Send(&pv[i].fx,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
      MPI_Send(&pv[i].fy,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
      MPI_Send(&pv[i].fz,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);
    }
  }
  MPI_Finalize();
  return 0;
}

double ComputeNewPos( Particle particles[], ParticleV pv[], int nParticles, double max_f)
{
  int i;
  double a0, a1, a2;
  double dt_new;
  a0   = 2.0 / (dt * (dt + dt_old));
  a2   = 2.0 / (dt_old * (dt + dt_old));
  a1   = -(a0 + a2);
  for (i=0; i<nParticles; i++) {
    double xi, yi;
    xi             = particles[i].x;
    yi             = particles[i].y;
    particles[i].x = (pv[i].fx - a1 * xi - a2 * pv[i].xold) / a0;
    particles[i].y = (pv[i].fy - a1 * yi - a2 * pv[i].yold) / a0;
    pv[i].xold     = xi;
    pv[i].yold     = yi;
    pv[i].fx       = 0;
    pv[i].fy       = 0;
  }
  dt_new = 1.0/sqrt(max_f);
  /* Set a minimum: */
  if (dt_new < 1.0e-6) dt_new = 1.0e-6;
  /* Modify time step */
  if (dt_new < dt) {
    dt_old = dt;
    dt     = dt_new;
  }
  else if (dt_new > 4.0 * dt) {
    dt_old = dt;
    dt    *= 2.0;
  }
  return dt_old;
}
