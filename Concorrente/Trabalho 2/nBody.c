#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
#include <stddef.h>
#define MODULUS    2147483647
#define MULTIPLIER 48271
#define DEFAULT    123456789

static long seed = DEFAULT;
double dt, dt_old;
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

typedef struct {
    double fx, fy, max_f;
} Forces;

typedef struct 
{
    Particle particle;
    ParticleV pv;
} BothParticles;

Forces ComputeForces(Particle [], int , int);
ParticleV InitParticleV( Particle, ParticleV );
Particle InitParticle( Particle, ParticleV, int);
double ComputeNewPos( Particle [], ParticleV [], int, double);
BothParticles ComputeNewPosParticle( Particle , ParticleV , double , double);
void ComputeNewDt(double);

int main(int argc, char **argv) {

    int size, rank, nParticles, timesteps;
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
 *  Tag 3 é o calculo da força do caso 1.
 *  Tag 4 para o caso 2.
 */
    int tmpNParticle = nParticles;
    //MASTER
    if (rank == 0) {
        Particle *particle = (Particle *) malloc(sizeof(Particle)*nParticles);
        ParticleV *pv = (ParticleV *) malloc(sizeof(ParticleV)*nParticles);

        // Caso 1 size > nParticles
        if (size > nParticles)  {
            for(int i = 1; i <= nParticles; i++)   {
                MPI_Recv(&pv[i-1], 1, mpi_particleV_type, i, 0, MPI_COMM_WORLD, &st );
                MPI_Recv(&particle[i-1], 1, mpi_particleV_type, i, 0, MPI_COMM_WORLD, &st );
            }
            // Envia as particulas para a primeira iteração
            for (int i = 1; i <= nParticles; i++)
                MPI_Send(particle,nParticles,mpi_particle_type,i,3,MPI_COMM_WORLD);
            
            while (timesteps--) {
                for (int i = 1; i <= nParticles; i++){
                    double max_f;
                    MPI_Recv(&pv[i-1], 1, mpi_particleV_type, i, 3, MPI_COMM_WORLD, &st );
                    MPI_Recv(&max_f, 1, MPI_DOUBLE, i, 3, MPI_COMM_WORLD, &st );
                    BothParticles bp;
                    bp = ComputeNewPosParticle(particle[i-1],pv[i-1],dt,dt_old);
                    particle[i-1] = bp.particle;
                    pv[i-1] = bp.pv;
                    ComputeNewDt(max_f);
                }
                // Envia as particulas paras as proximas iterações.
                for(int i = 1; i <= nParticles; i++){
                    MPI_Send(particle,nParticles,mpi_particle_type,i,3,MPI_COMM_WORLD);
                    MPI_Send(&pv[i-1],1,mpi_particleV_type,i,3,MPI_COMM_WORLD);
                }
            }
        }
        // Caso 2 nParticles >= size
        if (nParticles >= size){
            int i = 1;
            int computedParticle = 0;
            while(tmpNParticle >= size-1)   {
                for(i = 1;i < size; i++){
                    MPI_Send(&computedParticle, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
                    MPI_Recv(&pv[computedParticle], 1, mpi_particleV_type, i, 1, MPI_COMM_WORLD, &st );
                    MPI_Recv(&particle[computedParticle], 1, mpi_particleV_type, i, 1, MPI_COMM_WORLD, &st );
                    tmpNParticle--;
                    computedParticle++;
                }
            }

            /* Caso o modulo da quantidade de particulas pela quantidade de 
            processos - mestre for 1, signfica que faltou tratar uma particula */
            if (nParticles % (size-1) != 0) {
                int tmpModulo = nParticles % (size-1);
                while(tmpModulo > 0)    {
                    MPI_Send(&computedParticle, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
                    MPI_Recv(&pv[computedParticle], 1, mpi_particleV_type, 1, 1, MPI_COMM_WORLD, &st );
                    MPI_Recv(&particle[computedParticle], 1, mpi_particle_type, 1, 1, MPI_COMM_WORLD, &st );
                    tmpModulo--;
                    computedParticle++;
                }
            }
            //Todas as particulas teoricamente foram iniciadas...
            for (int i = 1; i < size; i++)
                MPI_Send(particle,nParticles,mpi_particle_type,i,4,MPI_COMM_WORLD);

            tmpNParticle = nParticles;
            computedParticle = 0;

            int tmpTimeSteps = timesteps;
            while(tmpTimeSteps--){
                while(tmpNParticle >= size-1)    {
                    for(int i = 1; i < size; i++)   {
                        double max_f;
                        MPI_Send(&computedParticle, 1, MPI_INT, i, 4, MPI_COMM_WORLD);
                        MPI_Recv(&pv[computedParticle], 1, mpi_particleV_type, i, 4, MPI_COMM_WORLD, &st);
                        MPI_Recv(&max_f, 1, MPI_DOUBLE, i, 4, MPI_COMM_WORLD, &st);
                        BothParticles bp;
                        bp = ComputeNewPosParticle(particle[computedParticle],pv[computedParticle],dt,dt_old);
                        particle[computedParticle] = bp.particle;
                        pv[computedParticle] = bp.pv;
                        ComputeNewDt(max_f);
                        tmpNParticle--;
                        computedParticle++;
                    }
                }
            }

            int tmpModulo = nParticles % (size-1);
            while(tmpModulo > 0)    {
                for(int i = timesteps; i > 0; i--){
                    double max_f;
                    MPI_Send(&computedParticle, 1, MPI_INT, 1, 4, MPI_COMM_WORLD);
                    MPI_Recv(&max_f, 1, MPI_DOUBLE, 1, 4, MPI_COMM_WORLD, &st);
                    MPI_Recv(&pv[computedParticle], 1, mpi_particleV_type, 1, 4, MPI_COMM_WORLD, &st);
                    BothParticles bp;
                    bp = ComputeNewPosParticle(particle[computedParticle],pv[computedParticle],dt,dt_old);
                    particle[computedParticle] = bp.particle;
                    pv[computedParticle] = bp.pv;
                    ComputeNewDt(max_f);
                }
                computedParticle++;
                tmpModulo--;
            }
        }            
    for (int i=0; i<nParticles; i++)
        fprintf(stdout,"%.5lf %.5lf\n", particle[i].x, particle[i].y);
    }
    //SLAVE
    else {
        Particle particles;
        ParticleV pv;
        int computedParticle;

        // Caso 2
        if (nParticles >= size){
            int whileXVezes = nParticles / (size-1);
            while (whileXVezes > 0)  {
                MPI_Recv(&computedParticle, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &st);
                particles = InitParticle(particles,pv,computedParticle);
                pv = InitParticleV(particles,pv);
                MPI_Send( &pv, 1, mpi_particleV_type, 0, 1, MPI_COMM_WORLD );  
                MPI_Send( &particles, 1, mpi_particle_type, 0, 1, MPI_COMM_WORLD );
                whileXVezes--;
            }
            /* Caso o modulo da quantidade de particulas pela quantidade de 
            processos - mestre for 1, signfica que faltou tratar uma particula */
            if(rank==1 && nParticles % (size-1) != 0)   {
                int tmpModulo = nParticles % (size-1);
                while(tmpModulo > 0)    {
                    MPI_Recv(&computedParticle, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &st);
                    particles = InitParticle(particles,pv,computedParticle);
                    pv = InitParticleV(particles,pv);
                    MPI_Send( &pv, 1, mpi_particleV_type, 0, 1, MPI_COMM_WORLD );  
                    MPI_Send( &particles, 1, mpi_particle_type, 0, 1, MPI_COMM_WORLD );
                    tmpModulo--;
                }
            }
            /* Calcular as forças */
            Particle *particleF = (Particle *) malloc(sizeof(Particle)*nParticles);
            MPI_Recv( particleF, nParticles, mpi_particle_type, 0, 4, MPI_COMM_WORLD, &st);

            Forces force;
            whileXVezes = nParticles / (size-1);
            int computedParticle;
            int tmpTimeSteps = timesteps;   
            while(tmpTimeSteps--){
                while (whileXVezes > 0)  {
                    MPI_Recv(&computedParticle, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, &st);
                    force = ComputeForces(particleF,computedParticle,nParticles);
                    double max_f;
                    pv.fx += force.fx;
                    pv.fy += force.fy;
                    max_f = force.max_f;
                    MPI_Send( &pv, 1, mpi_particleV_type, 0, 4, MPI_COMM_WORLD );  
                    MPI_Send( &max_f,1,MPI_DOUBLE,0,4,MPI_COMM_WORLD);
                    whileXVezes--;
                }
            }

            if(rank==1 && nParticles % (size-1) != 0)   {
                int tmpModulo = nParticles % (size-1);
                while(tmpModulo > 0)    {
                    for(int i = timesteps; i > 0; i--){
                        MPI_Recv(&computedParticle, 1, MPI_INT, 0, 4, MPI_COMM_WORLD, &st);
                        force = ComputeForces(particleF,computedParticle,nParticles);
                        double max_f;
                        pv.fx += force.fx;
                        pv.fy += force.fy;
                        max_f = force.max_f;
                        MPI_Send( &max_f, 1, MPI_DOUBLE, 0, 4, MPI_COMM_WORLD );  
                        MPI_Send( &pv, 1 , mpi_particleV_type, 0, 4, MPI_COMM_WORLD);
                    }
                tmpModulo--; 
                }
            }
      }

        // Caso 1
        if (size > nParticles && rank <= nParticles)  {
            particles = InitParticle(particles,pv,rank);
            pv = InitParticleV(particles,pv);
            MPI_Send( &pv, 1, mpi_particleV_type, 0, 0, MPI_COMM_WORLD );  
            MPI_Send( &particles, 1, mpi_particle_type, 0, 0, MPI_COMM_WORLD );
            Particle *particleF = (Particle *) malloc(sizeof(Particle)*nParticles);
            MPI_Recv( particleF, nParticles, mpi_particle_type, 0, 3, MPI_COMM_WORLD, &st);

            /* CALCULAR A FORÇA! */
            Forces force;
            while (timesteps--) {
                    force = ComputeForces(particleF,rank,nParticles);
                    double max_f;
                    pv.fx += force.fx;
                    pv.fy += force.fy;
                    max_f = force.max_f;
                    MPI_Send( &pv, 1, mpi_particleV_type, 0, 3, MPI_COMM_WORLD );  
                    MPI_Send( &max_f,1,MPI_DOUBLE,0,3,MPI_COMM_WORLD);
                    MPI_Recv( particleF, nParticles, mpi_particle_type, 0, 3, MPI_COMM_WORLD, &st);
                    MPI_Recv( &pv, 1, mpi_particleV_type, 0, 3, MPI_COMM_WORLD, &st);
                }
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

BothParticles ComputeNewPosParticle( Particle particle, ParticleV pv, double dt, double dt_old)
{
  BothParticles bp;
  double a0, a1, a2;
  double xi, yi;
  a0     = 2.0 / (dt * (dt + dt_old));
  a2     = 2.0 / (dt_old * (dt + dt_old));
  a1     = -(a0 + a2);
  xi             = particle.x;
  yi             = particle.y;
  bp.particle.x = (pv.fx - a1 * xi - a2 * pv.xold) / a0;
  bp.particle.y = (pv.fy - a1 * yi - a2 * pv.yold) / a0;
  bp.pv.xold     = xi;
  bp.pv.yold     = yi;
  bp.pv.fx       = 0;
  bp.pv.fy       = 0;
 return bp;
}

void ComputeNewDt(double max_f)
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
}

Forces ComputeForces(Particle particle[], int rank, int nParticles)
{
    Forces force;
    int i,j;
    double xi, yi, mi, rx, ry, mj, r, fx, fy, rmin, max_f;
    max_f = 0.0;
    rmin = 100.0;
    xi   = particle[rank-1].x;
    yi   = particle[rank-1].y;
    fx   = 0.0;
    fy   = 0.0;
    for (j=0; j<nParticles; j++) {
        rx = xi - particle[j].x;
        ry = yi - particle[j].y;
        mj = particle[j].mass;
        r  = rx * rx + ry * ry;
        /* ignore overlap and same particle */ 
        if (r == 0.0) continue;
        if (r < rmin) rmin = r;
        r  = r * sqrt(r);
        fx -= mj * rx / r;
        fy -= mj * ry / r;
    }
    force.fx = fx;
    force.fy = fy;
    fx = sqrt(fx*fx + fy*fy)/rmin;
    if (fx > max_f) max_f = fx;
    force.max_f = max_f;
    return force;
}