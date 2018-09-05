#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS
	#pragma warning(disable:4996)
#endif

#define OP_NOT_FOUND	-1;
#define INSERT			0;
#define REMOVE			1;
#define AVG_SAL			2;
#define EXPORT_TXT		3;
#define COMPRESS		4;

void showinfo() {
	char* usage =
		"\n"
		"Uso:\n<NomeDoPrograma> <NomeDaBaseDeDados> <operacao>\n"
			"\tOperacoes:\n"
				"\t\tins  -  insere um funcionario na base de dados.\n"
				"\t\trem  -  remove um funcionario da base de dados.\n"
				"\t\tmed  -  calcula a media dos salarios por sexo.\n"
				"\t\texp  -  exporta as informacoes da base de dados em um arquivo txt.\n"
				"\t\tcpc  -  remove da base de dados as informacoes desnecessarias.\n";
	printf(usage);
}

typedef struct funcionario {
	unsigned int id;
	char nome[256];
	char sexo;
	float salario;
}funcionario;

FILE* openDatabase(char* db) {
	FILE* fp;
	fp = fopen(db, "r+b");
	if (fp == NULL) {
		fp = fopen(db, "a+b");
		fclose(fp);
		fp = fopen(db, "r+b");
	}
	return fp;
}

size_t readDatabase(FILE* db, funcionario** func) {
	fseek(db, 0, SEEK_END);
	long fsize = ftell(db);
	fseek(db, 0, SEEK_SET); 
	*func = (funcionario*)malloc(fsize + 1);
	fread(*func, fsize, 1, db);
	return fsize / sizeof(funcionario);
}

void insertFunc(FILE* db) {
	funcionario* func = NULL;
	size_t numFuncs = readDatabase(db, &func);
	funcionario f;
	for (;;) {
		printf("\nInsira o ID do funcionario: ");
		int id;
		scanf("\n%i", &id);
		if (id <= 0) {
			printf("\nO ID do funcionario deve ser um numero positivo.\n");
			continue;
		}
		int good = 1;
		for (unsigned int i = 0; i < numFuncs; ++i) {
			funcionario f = *(func + i);
			if ((unsigned int)id == f.id) {
				printf("\nID ja existe.\n");
				good = 0;
				break;
			}
		}
		if (good == 0) {
			continue;
		}
		f.id = (unsigned int)id;
		break;
	}

	printf("\nInsira o nome do funcionario: ");
	scanf("%s", f.nome);

	for (;;) {
		printf("\nInsira o sexo do funcionario (M ou F): ");
		char sexo;
		scanf("\n%c", &sexo);
		if (sexo != 'M' && sexo != 'F') {
			continue;
		}
		f.sexo = sexo;
		break;
	}

	float salario;
	printf("\nInsira o salario do funcionario: ");
	scanf("%f", &salario);
	f.salario = salario;
	const void *ptr = (void*)(&f);
	fseek(db, 0, SEEK_END);
	fwrite(ptr, sizeof(funcionario), 1, db);

	free(func);
	fclose(db);
	printf("\nFuncionario %i inserido com exito: ", f.id);
	return;
}

void removeFunc(FILE* db) {
	funcionario* func = NULL;
	size_t numFuncs = readDatabase(db, &func);
	for (;;) {
		unsigned int numValidFuncs = 0;
		for (unsigned int i = 0; i < numFuncs; ++i) {
			funcionario f = *(func + i);
			if (f.id != 0) {
				numValidFuncs++;
			}
		}
		if (numValidFuncs == 0) {
			printf("\nNada a remover, banco vazio.\n");
			return;
		}
		int id;
		printf("\nInsira o ID do funcionario a ser removido: ");
		scanf("\n%i", &id);
		if (id <= 0) {
			printf("\nO ID do funcionario deve ser um numero positivo.\n");
			continue;
		}
		int good = 0;
		for (unsigned int i = 0; i < numFuncs; ++i) {
			funcionario f = *(func + i);
			if ((unsigned int)id == f.id) {
				fseek(db, i * sizeof(funcionario), SEEK_SET);
				unsigned int zero = 0;
				fwrite((void*)(&zero), sizeof(unsigned int), 1, db);
				printf("\nFuncionario com ID %i removido.\n", id);
				good = 1;
				break;
			}
		}
		if (good == 0) {
			printf("\nID inexistente.\n");
			continue;
		}
		break;
	}

	free(func);
	fclose(db);
	return;
}

void avg_sal(FILE* db) {
	funcionario* func = NULL;
	size_t numFuncs = readDatabase(db, &func);
	unsigned int numM = 0;
	unsigned int numF = 0;
	float totSalM = 0;
	float totSalF = 0;
	for (unsigned int i = 0; i < numFuncs; ++i) {
		funcionario f = *(func + i);
		if (f.id == 0) {
			continue;
		}
		if (f.sexo == 'M') {
			numM++;
			totSalM += f.salario;
		}
		if (f.sexo == 'F') {
			numF++;
			totSalF += f.salario;
		}
	}
	if (numM == 0) {
		printf("\nNao ha funcionarios homens cadastrados no banco.\n");
	}
	else {
		printf("\nMedia dos salarios dos homens: %f\n", (totSalM / numM));
	}
	if (numF == 0) {
		printf("\nNao ha funcionarias mulheres cadastradas no banco.\n");
	}
	else {
		printf("\nMedia dos salarios das mulheres: %f\n", (totSalF / numF));
	}

	free(func);
	fclose(db);
	return;

}
void exportTxt(FILE* db) {
	printf("\nInsira o nome do arquivo de saida (com extensao .txt): ");
	char filename[256];
	scanf("%s", filename);

	FILE* fp = fopen(filename, "w");
	funcionario* func = NULL;
	size_t numFuncs = readDatabase(db, &func);
	for (unsigned int i = 0; i < numFuncs; ++i) {
		funcionario f = *(func + i);
		if (f.id == 0) {
			continue;
		}
		int id = f.id;

		fprintf(fp, "ID = %i\n", f.id);
		fprintf(fp, "Nome = %s\n", f.nome);
		fprintf(fp, "Sexo = %c\n", f.sexo);
		fprintf(fp, "Salario = %f\n\n", f.salario);
	}
	fclose(fp);

	free(func);
	fclose(db);
	return;
}
void compressDb(FILE* db) {
	funcionario* func = NULL;
	size_t numFuncs = readDatabase(db, &func);
	unsigned int validFunc = 0;
	for (unsigned int i = 0; i < numFuncs; ++i) {
		funcionario f = *(func + i);
		if (f.id > 0) {
			validFunc++;
		}
	}
	funcionario* cpcFunc = (funcionario*)malloc(validFunc * sizeof(funcionario));
	unsigned int cpcFuncIdx = 0;
	for (unsigned int i = 0; i < numFuncs; ++i) {
		funcionario f = *(func + i);
		if (f.id > 0) {
			cpcFunc[cpcFuncIdx] = f;
			cpcFuncIdx++;
		}
	}
	freopen("db_compressed.db", "w", db);
	const void *ptr = (void*)(cpcFunc);
	fwrite(ptr, sizeof(funcionario), validFunc, db);

	free(func);
	free(cpcFunc);
	fclose(db);

	return;

}

void (*operations[])(FILE*) = { insertFunc , removeFunc, avg_sal, exportTxt, compressDb };

int checkoperation(char* op) {
	int found = 0;
	if (strcmp(op, "ins") == 0) {
		return INSERT;
	}
	if (strcmp(op, "rem") == 0) {
		return REMOVE;
	}
	if (strcmp(op, "med") == 0) {
		return AVG_SAL;
	}
	if (strcmp(op, "exp") == 0) {
		return EXPORT_TXT;
	}
	if (strcmp(op, "cpc") == 0) {
		return COMPRESS;
	}
	return OP_NOT_FOUND;
}

void finish() {
#ifdef _MSC_VER
	system("pause");
#else
	printf("\npressione qualquer tecla para sair");
	char ch;
	scanf("\n%c", &ch);
#endif
	return;
}

int main(int argc, char* argv[]) {

	if (argc != 3) {
		showinfo();
		finish();
		return 0;
	}
	int opID = checkoperation(argv[2]);
	if (opID == -1) {
		showinfo();
		finish();
		return 0;
	}
	else {
		FILE* db = openDatabase(argv[1]);
		if (db != NULL) {
			(*operations[opID])(db);
		}
	}

	finish();
	return;
}