
CREATE TABLE Prestador(
    códigocnpj varchar(14) PRIMARY KEY, 
    nome varchar(70), 
    CNES varchar(7)
);

CREATE TABLE Beneficiario(
    nCarteira varchar(20) PRIMARY KEY, 
    plano varchar(40), 
    validadeCarteira Date, 
    nome varchar(70), 
    nCartãoNacionalSaude varchar(15)
);

CREATE TABLE CaráterInternação(
    id varchar(1) PRIMARY KEY, 
    descricao varchar(60)
);

CREATE TABLE TiposDeInternação(
    id smallint PRIMARY KEY, 
    descricao varchar(60)
);

CREATE TABLE RegimeDeInternação(
    id smallint PRIMARY KEY, 
    descricao varchar(60)
);

CREATE TABLE UF(
    sigla varchar(2) PRIMARY KEY, 
    nome varchar(20)
);

CREATE TABLE Conselho(
    numeroConselho varchar(15) PRIMARY KEY, 
    conselhoProfissional varchar(7), 
    sigla varchar(2) REFERENCES UF
);

CREATE TABLE Ocupação(
    CBO varchar(5) PRIMARY KEY, 
    Nome varchar(40) 
);

CREATE TABLE Estabelecimento(
    CNES varchar(7) PRIMARY KEY, 
    Nome varchar(40)
);

CREATE TABLE Solicitante(
    CPFouCNPJ varchar(14) PRIMARY KEY,
    nomeSolicitante varchar(70),
    numeroConselho varchar(15) REFERENCES Conselho,
    numeroNoConselho varchar(15)
);

CREATE TABLE Procedimento(
    código varchar(10) PRIMARY KEY, 
    descrição varchar(60) 
);

CREATE TABLE Fabricante(
    código varchar(2) PRIMARY KEY, 
    nome varchar(40) 
);

CREATE TABLE OPM(
    código varchar(10) PRIMARY KEY, 
    descrição varchar(60), 
    valorUnitario numeric(9,2), 
    códigoFabricante varchar(2) REFERENCES Fabricante 
);

CREATE TABLE TipoAcomodação(
    código varchar(2) PRIMARY KEY, 
    descrição varchar(60)
);

CREATE TABLE Solicitação(
    id serial PRIMARY KEY, 
    data Date, 
    dataValidade Date, 
    dataEmissao Date, 
    registroANS varchar(6), 
    senha varchar(20), 
    nCartãoNacionalSaude varchar(15) REFERENCES Beneficiario, 
    CPFouCNPJ varchar(14) REFERENCES Solicitante,
    códigocnpj varchar(14) REFERENCES Prestador,
    
    diarias int, 
    indicaçãoClínica varchar(500), 
    idCaráter varchar(1) REFERENCES CaráterInternação,
    idTipo smallint REFERENCES TiposDeInternação,
    idRegime smallint REFERENCES RegimeDeInternação
);

CREATE TABLE Autorização(
    codAutorização serial PRIMARY KEY,
    qteDiariasAut int, 
    dataProvAdmissao Date, 
    observação varchar(240), 
    códigocnpj varchar(14), 
    código varchar(2), 
    id int REFERENCES Solicitação, 
    códigoAcomodação varchar(2) REFERENCES TipoAcomodação
);

CREATE TABLE Prorrogação(
    código serial PRIMARY KEY,
    data Date, 
    senha varchar(20), 
    qtdDiariasAut int, 
    códigoAcomodação varchar(2) REFERENCES TipoAcomodação
);

CREATE TABLE Hipótese(
    CID10 varchar(5) PRIMARY KEY, 
    descrição varchar(100)

);

CREATE TABLE TipoDoença(
    código varchar(1) PRIMARY KEY, 
    id int REFERENCES Solicitação,
    descrição varchar(100)
);

CREATE TABLE TempoDoença(
    código varchar(1) PRIMARY KEY, 
    id int REFERENCES Solicitação,
    descrição varchar(100)

);

CREATE TABLE IndicadorAcidente(
    código smallint PRIMARY KEY, 
    id int REFERENCES Solicitação,
    descrição varchar(100)
);

CREATE TABLE TabelaDomínio(
    código varchar(2) PRIMARY KEY, 
    descrição varchar(60)
);

CREATE TABLE SolicitaçãoTipoDoença(
    cod serial PRIMARY KEY,
    id int REFERENCES Solicitação, 
    código varchar(1) REFERENCES TipoDoença
);

CREATE TABLE SolicitaçãoIndicadorAcidente(
    cod serial PRIMARY KEY,
    id int REFERENCES Solicitação, 
    código smallint REFERENCES IndicadorAcidente
);

CREATE TABLE SolicitaçãoTempoDoença(
    cod serial PRIMARY KEY,
    id int REFERENCES Solicitação, 
    código varchar(1) REFERENCES TempoDoença 
);

CREATE TABLE SolicitaçãoOPM(
    código varchar(10) REFERENCES OPM PRIMARY KEY,
    cod serial, 
    id int REFERENCES Solicitação,
    quantidade int
);

CREATE TABLE SolicitaçãoProcedimento(
    cod serial PRIMARY KEY,
    id int REFERENCES Solicitação, 
    código varchar(10) REFERENCES Procedimento,
    qtdAutorizada int,
    qtdSolicitada int
);

CREATE TABLE SolicitaçãoProrrogação(
    cod serial PRIMARY KEY,
    id int REFERENCES Solicitação,
    código int REFERENCES Prorrogação
);

CREATE TABLE SolicitanteEstabelecimento(
    cod serial PRIMARY KEY,
    CPFouCNPJ varchar(14) REFERENCES Solicitante,
    CNES varchar(7) REFERENCES Estabelecimento
);

CREATE TABLE SolicitanteOcupação(
    cod serial PRIMARY KEY,
    CPFouCNPJ varchar(14) REFERENCES Solicitante,
    CBO varchar(5) REFERENCES Ocupação
);

CREATE TABLE OPMTabelaDomínio(
    cod serial PRIMARY KEY,
    códigoOPM varchar(10) REFERENCES OPM,
    códigoTabela varchar(2) REFERENCES TabelaDomínio
);

CREATE TABLE ProcedimentoTabelaDomínio(
    cod serial PRIMARY KEY,
    códigoProc varchar(10) REFERENCES Procedimento,
    códigoTabela varchar(2) REFERENCES TabelaDomínio
);

CREATE TABLE ProcedimentoProrrogação(
    cod serial PRIMARY KEY,
    códigoProc varchar(10) REFERENCES Procedimento,
    códigoProrrog int REFERENCES Prorrogação,
    qtdAutorizada int,
    qtdSolicitada int

);

CREATE TABLE OPMProrrogação(
    cod serial PRIMARY KEY,
    códigoOPM varchar(10) REFERENCES OPM,
    códigoProrrog int REFERENCES Prorrogação,
    quantidade int
);

CREATE TABLE HipóteseSolicitação(
    cod serial PRIMARY KEY,
    CID10 varchar(5) REFERENCES Hipótese,
    id int REFERENCES Solicitação,
    rank int
);
    

