#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <stddef.h>
#define MODULUS    2147483647
#define MULTIPLIER 48271
#define DEFAULT    12345678

static long seed = DEFAULT;
double dt, dt_old;
int numeroDeParticulasQueFaltam;
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

typedef struct {
    double x, y, z;
    double mass;
} Particle;

typedef struct {
    double xold, yold, zold;
    double fx, fy, fz;
} ParticleV;

ParticleV InitParticleV( Particle, ParticleV );
Particle InitParticle( Particle, ParticleV, int);
double ComputeNewPos( Particle [], ParticleV [], int, double);
Particle ComputeNewPosParticle( Particle , ParticleV , double , double);
double ComputeNewDt(double);
ParticleV ComputeNewPosParticleV(ParticleV , double , double );

int main(int argc, char **argv) {

    const int tag = 13;
    int size, rank, nParticles, timesteps;
    double sim_t;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status st;

    if(argc != 3){
        printf("Wrong number of parameters.\nUsage: nbody num_bodies timesteps\n");
        exit(1);
    }

    nParticles = atoi(argv[1]);
    timesteps = atoi(argv[2]);
    dt = 0.001; 
    dt_old = 0.001;
    sim_t = 0.0;

    /* create a type for struct car */
    const int nitems=4;
    int          blocklengths[4] = {1,1,1,1};
    MPI_Datatype types[4] = {MPI_DOUBLE, MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE};
    MPI_Datatype mpi_particle_type;
    MPI_Aint     offsets[4];

    offsets[0] = offsetof(Particle, x);
    offsets[1] = offsetof(Particle, y);
    offsets[2] = offsetof(Particle, z);
    offsets[3] = offsetof(Particle, mass);

    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_particle_type);
    MPI_Type_commit(&mpi_particle_type);

    const int nitemsV=6;
    int          blocklengthsV[6] = {1,1,1,1,1,1};
    MPI_Datatype typesV[6] = {MPI_DOUBLE, MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE,MPI_DOUBLE};
    MPI_Datatype mpi_particleV_type;
    MPI_Aint     offsetsV[6];

    offsetsV[0] = offsetof(ParticleV, xold);
    offsetsV[1] = offsetof(ParticleV, yold);
    offsetsV[2] = offsetof(ParticleV, zold);
    offsetsV[3] = offsetof(ParticleV, fx);
    offsetsV[4] = offsetof(ParticleV, fy);
    offsetsV[5] = offsetof(ParticleV, fz);

    MPI_Type_create_struct(nitemsV, blocklengthsV, offsetsV, typesV, &mpi_particleV_type);
    MPI_Type_commit(&mpi_particleV_type);

/*  Numero de processos = size
 *  Numero de particulas = nParticle
 *  size > nParticle Pode mandar uma particula para cada processo.   Tag 0
 *  nParticle >= size Enviar uma particula, receber e mandar outro.  Tag 1
 *  Tag 3 é o calculo da força.
 */
    int numeroDeParticulasQueFaltam = nParticles;
    //MASTER
    if (rank == 0) {
        Particle *particle = (Particle *) malloc(sizeof(Particle)*nParticles);
        ParticleV *pv = (ParticleV *) malloc(sizeof(ParticleV)*nParticles);

            // Caso 1
        if (size > nParticles)  {
            for(int i = 1; i <= nParticles; i++)   {
                MPI_Recv(&pv[i-1], 1, mpi_particleV_type, i, 0, MPI_COMM_WORLD, &st );
                MPI_Recv(&particle[i-1], 1, mpi_particleV_type, i, 0, MPI_COMM_WORLD, &st );
            }
            for (int i = 1; i < nParticles+1; i++)
                MPI_Send(particle,nParticles,mpi_particle_type,i,3,MPI_COMM_WORLD);
            while (timesteps--) {
                for (int i = 1; i < nParticles+1; i++){
                    double max_f;
                    MPI_Recv(&pv[i-1], 1, mpi_particleV_type, i, 3, MPI_COMM_WORLD, &st );
                    MPI_Recv(&max_f, 1, MPI_DOUBLE, i, 3, MPI_COMM_WORLD, &st );
                    particle[i-1] = ComputeNewPosParticle(particle[i-1],pv[i-1],dt,dt_old);
//                    pv[i-1] = ComputeNewPosParticleV(pv[i-1],xi,yi);
                    dt_old = ComputeNewDt(max_f);
                    MPI_Send(particle,nParticles,mpi_particle_type,i,3,MPI_COMM_WORLD);
                }

            }
      for (int i=0; i<nParticles; i++)
        fprintf(stdout,"%.5lf %.5lf\n", particle[i].x, particle[i].y);

        }
            // Caso 2
        if (nParticles >= size){
            int i = 1;
            int numeroDeParticulasQueJaForam = 0;
            while(numeroDeParticulasQueFaltam >= size-1)   {
                for(i;i < size; i++){
                    MPI_Send(&numeroDeParticulasQueFaltam, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
                    MPI_Recv(&pv[numeroDeParticulasQueJaForam], 1, mpi_particleV_type, i, 1, MPI_COMM_WORLD, &st );
                    MPI_Recv(&particle[numeroDeParticulasQueJaForam], 1, mpi_particleV_type, i, 1, MPI_COMM_WORLD, &st );
                    numeroDeParticulasQueFaltam--;
                    numeroDeParticulasQueJaForam++;
                }
                i = 1;
            }
            /* Caso o modulo da quantidade de particulas pela quantidade de 
            processos - mestre for 1, signfica que faltou tratar uma particula */
            if (nParticles % (size-1) == 1) {
                MPI_Send(&numeroDeParticulasQueFaltam, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
                MPI_Recv(&pv[numeroDeParticulasQueJaForam], 1, mpi_particleV_type, 1, 1, MPI_COMM_WORLD, &st );
                MPI_Recv(&particle[numeroDeParticulasQueJaForam], 1, mpi_particleV_type, 1, 1, MPI_COMM_WORLD, &st );
            }
        }
    }
    //SLAVE
    else {
        Particle particles;
        ParticleV pv;

        // Caso 2
        if (nParticles >= size){
            int whileXVezes = nParticles / (size-1);
            numeroDeParticulasQueFaltam - size-1;

            while (whileXVezes > 0)  {
                int numeroDeParticulasQueFaltam;
                MPI_Recv(&numeroDeParticulasQueFaltam, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &st);
                particles = InitParticle(particles,pv,numeroDeParticulasQueFaltam);
                pv = InitParticleV(particles,pv);
                MPI_Send( &pv, 1, mpi_particleV_type, 0, 1, MPI_COMM_WORLD );  
                MPI_Send( &particles, 1, mpi_particle_type, 0, 1, MPI_COMM_WORLD );
                whileXVezes--;
            }
            /* Caso o modulo da quantidade de particulas pela quantidade de 
            processos - mestre for 1, signfica que faltou tratar uma particula */
        if(rank==1 && nParticles % (size-1) == 1)   {
                int numeroDeParticulasQueFaltam;
                MPI_Recv(&numeroDeParticulasQueFaltam, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &st);
                particles = InitParticle(particles,pv,numeroDeParticulasQueFaltam);
                pv = InitParticleV(particles,pv);
                MPI_Send( &pv, 1, mpi_particleV_type, 0, 1, MPI_COMM_WORLD );  
                MPI_Send( &particles, 1, mpi_particle_type, 0, 1, MPI_COMM_WORLD );
            }
        }

        // Caso 1
        if (size > nParticles && rank <= nParticles)  {
            particles = InitParticle(particles,pv,rank);
            pv = InitParticleV(particles,pv);
            MPI_Send( &pv, 1, mpi_particleV_type, 0, 0, MPI_COMM_WORLD );  
            MPI_Send( &particles, 1, mpi_particle_type, 0, 0, MPI_COMM_WORLD );
            Particle *particleF = (Particle *) malloc(sizeof(Particle)*nParticles);
            ParticleV *pvF = (ParticleV *) malloc(sizeof(ParticleV)*nParticles);

            /* CALCULAR A FORÇA! */

            while (timesteps--) {
                    double max_f;
                    int i;
                    max_f = 0.0;
                    int j;
                    double xi, yi, mi, rx, ry, mj, r, fx, fy, rmin;
                    rmin = 100.0;
                    xi   = particleF[rank-1].x;
                    yi   = particleF[rank-1].y;
                    fx   = 0.0;
                    fy   = 0.0;
                    for (j=0; j<nParticles; j++) {
                        rx = xi - particleF[j].x;
                        ry = yi - particleF[j].y;
                        mj = particleF[j].mass;
                        r  = rx * rx + ry * ry;
                        /* ignore overlap and same particle */ 
                        if (r == 0.0) continue;
                        if (r < rmin) rmin = r;
                        r  = r * sqrt(r);
                        fx -= mj * rx / r;
                        fy -= mj * ry / r;
                    }
                    //Isso tem que enviar para o master pq vai importar no proximo calculo.
                    pv.fx += fx;
                    pv.fy += fy;
                    MPI_Send( &pv, 1, mpi_particleV_type, 0, 3, MPI_COMM_WORLD );  
                    fx = sqrt(fx*fx + fy*fy)/rmin;
                    if (fx > max_f) max_f = fx;
                    MPI_Send(&max_f,1,MPI_DOUBLE,0,3,MPI_COMM_WORLD);
                    MPI_Recv( particleF, nParticles, mpi_particle_type, 0, 3, MPI_COMM_WORLD, &st);
                    //Cada particula tem seu max_f...

                    /* CALCULAR A NOVA POSIÇÂO! */
/*
                    MPI_Recv(&dt,);
                    MPI_Recv(&dt_old,);

                    double a0, a1, a2;
                    a0     = 2.0 / (dt * (dt + dt_old));
                    a2     = 2.0 / (dt_old * (dt + dt_old));
                    a1     = -(a0 + a2);
                    xi             = particleF[rank-1].x;
                    yi             = particleF[rank-1].y;
                    particleF[rank-1].x = (pv.fx - a1 * xi - a2 * pv.xold) / a0;
                    particleF[rank-1].y = (pv.fy - a1 * yi - a2 * pv.yold) / a0;
                    pv.xold     = xi;
                    pv.yold     = yi;
                    pv.fx       = 0;
                    pv.fy       = 0;

                    double dt_new;
                    dt_new = 1.0/sqrt(max_f);
                    /* Set a minimum: */
/*                    if (dt_new < 1.0e-6) dt_new = 1.0e-6;
                    /* Modify time step
                       DT e DT_OLD são globais, não dá para tratar em cada particula
                       mandar para mestre que ele resolve */
/*                    if (dt_new < dt) {
                        dt_old = dt;
                        dt     = dt_new;
                    }
                    else if (dt_new > 4.0 * dt) {
                        dt_old = dt;
                        dt    *= 2.0;
                    }

                    MPI_Send(&dt,);
                    MPI_Send(&dt_old),;
*/                }
    }
}
    MPI_Type_free(&mpi_particle_type);
    MPI_Type_free(&mpi_particleV_type);
    MPI_Finalize();
    return 0;
}

ParticleV InitParticleV( Particle particles, ParticleV pv)
{
            pv.xold    = particles.x;
            pv.yold    = particles.y;
            pv.zold    = particles.z;
            pv.fx    = 0;
            pv.fy    = 0;
            pv.fz    = 0;
            return pv;
}

Particle InitParticle( Particle particles, ParticleV pv, int valor)
{
            seed = seed+valor;
            particles.x    = Random();
            particles.y    = Random();
            particles.z    = Random();
            particles.mass = 1.0;
            return particles;
}

Particle ComputeNewPosParticle( Particle particles, ParticleV pv, double dt, double dt_old)
{
  double a0, a1, a2;
  double xi, yi;
  a0     = 2.0 / (dt * (dt + dt_old));
  a2     = 2.0 / (dt_old * (dt + dt_old));
  a1     = -(a0 + a2);
  xi             = particles.x;
  yi             = particles.y;
  particles.x = (pv.fx - a1 * xi - a2 * pv.xold) / a0;
  particles.y = (pv.fy - a1 * yi - a2 * pv.yold) / a0;
 return particles;
}

ParticleV ComputeNewPosParticleV(ParticleV pv, double xi, double yi)
{
  pv.xold     = xi;
  pv.yold     = yi;
  pv.fx       = 0;
  pv.fy       = 0;
  return pv;
}

double ComputeNewDt(double max_f)
{
  double dt_new;
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