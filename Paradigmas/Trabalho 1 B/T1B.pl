/* Nome: Fábio Volkmann Coelho
   Matricula: 15200589

   Currículo para o T1: Educação Física - Licenciatura
*/

fase(def5829, 1).
fase(def5835, 1).
fase(def5843, 1).
fase(def5844, 1).
fase(def5884, 1).
fase(def5894, 1).
fase(mor5219, 1).
fase(cfs5148, 2).
fase(def5807, 2).
fase(def5845, 2).
fase(def5846, 2).
fase(def5870, 2).
fase(def5886, 2).
fase(def5893, 2).
fase(def5896, 2).
fase(men5164, 2).
fase(def5810, 3).
fase(def5847, 3).
fase(def5848, 3).
fase(def5897, 3).
fase(def5898, 3).
fase(eed5331, 3).
fase(psi5137, 3).
fase(def5818, 4).
fase(def5849, 4).
fase(def5850, 4).
fase(def5869, 4).
fase(def5887, 4).
fase(eed5187, 4).
fase(men5603, 4).
fase(def5821, 5).
fase(def5840, 5).
fase(def5841, 5).
fase(def5871, 5).
fase(def5885, 5).
fase(def5890, 5).
fase(men5186, 5).
fase(def5808, 6).
fase(def5826, 6).
fase(def5872, 6).
fase(men5321, 6).
fase(def5873, 7).
fase(def5874, 7).
fase(eed5188, 7).
fase(men5322, 7).
fase(def5875, 8).
fase(def5899, 8).
fase(lsb7904, 8).

disciplina(def5829, 1, "Teoria e Metodologia do Atletismo I").
disciplina(def5835, 1, "Teoria e Metodologia da Ginástica").
disciplina(def5843, 1, "Teoria e Metodologia do Futebol").
disciplina(def5844, 1, "Teoria e Metodologia do Handebol").
disciplina(def5884, 1, "Fundamentos Histórico - Pedagógicos da Educação Física").
disciplina(def5892, 1, "Crescimento e Desenvolvimento Humano").
disciplina(def5894, 1, "Metodologia do Trabalho Acadêmico").
disciplina(mor5219, 1, "Anatomia Aplicada à Educação Física").
disciplina(cfs5148, 2, "Fisiologia Humana").
disciplina(def5807, 2, "Fundamentos Sócio-Antropológicos da Educação Física").
disciplina(def5845, 2, "Teoria e Metodologia do Basquetebol").
disciplina(def5846, 2, "Teoria e Metodologia do Futsal").
disciplina(def5870, 2, "Seminário Pedagógico em Educação Física").
disciplina(def5886, 2, "Fundamentos Teórico - Metodológicos do Lazer").
disciplina(def5893, 2, "Aprendizagem e Controle Motor").
disciplina(def5896, 2, "Teoria e Metodologia da Natação").
disciplina(men5164, 2, "Seminário Pedagógico em Educação Física").
disciplina(def5810, 3, "Planejamento e Organização de Eventos").
disciplina(def5847, 3, "Teoria-Metodologia-Voleibol").
disciplina(def5848, 3, "Teoria e Metodologia do Tênis").
disciplina(def5897, 3, "Adaptações Orgânicas ao Exercício").
disciplina(def5898, 3, "Biomecânica").
disciplina(eed5331, 3, "Teorias da Educação").
disciplina(psi5137, 3, "Psicologia Educacional: Desenvolvimento e Aprendizagem").
disciplina(def5818, 4, "Educação Física Adaptada").
disciplina(def5849, 4, "Teoria e Metodologia do Judô").
disciplina(def5850, 4, "Teoria e Metodologia da Capoeira").
disciplina(def5869, 4, "Jogos e Brinquedos da Cultura Popular").
disciplina(def5887, 4, "Fundamentos Teórico - Metodológicos da Dança").
disciplina(eed5187, 4, "Organização Escolar").
disciplina(men5603, 4, "Didática C").
disciplina(def5821, 5, "Medidas de Avaliações em Educação Física A").
disciplina(def5840, 5, "Teoria e Metodologia dos Esportes Adaptados").
disciplina(def5841, 5, "Teoria e Metodologia dos Esportes de Aventura").
disciplina(def5871, 5, "Metodologia - Ensino - Educação Física").
disciplina(def5885, 5, "Educação Física na Infância").
disciplina(def5890, 5, "Educação Física - Saúde - Qualidade de Vida").
disciplina(men5186, 5, "Metodologia do Ensino da Educação Física").
disciplina(def5808, 6, "Princípios de Conduta Profissional A").
disciplina(def5826, 6, "Metodologia da Pesquisa em Educação Física").
disciplina(def5872, 6, "Estágio Supervisionado em Educação Física I").
disciplina(men5321, 6, "Estágio Supervisionado em Educação Física I").
disciplina(def5873, 7, "Estágio Supervisionado em Educação Física II").
disciplina(def5874, 7, "Seminário de Conclusão de Curso I").
disciplina(eed5188, 7, "Seminário Temático/Educação/Processos Inclusivos").
disciplina(men5322, 7, "Estágio Supervisionado em Educação Física II").
disciplina(def5875, 8, "Seminário de Conclusão de Curso II").
disciplina(def5899, 8, "Atividades Acadêmico-Científico-Culturais").
disciplina(lsb7904, 8, "Língua Brasileira de Sinais").

requisito(cfs5148, mor5219).
requisito(def5897, cfs5148).
requisito(def5898, mor5219).
requisito(def5840, def5818).
requisito(def5826, men5603).
requisito(def5885, def5892).
requisito(def5872, def5870).
requisito(def5872, eed5331).
requisito(def5872, eed5187).
requisito(def5872, men5603).
requisito(def5872, def5871).
requisito(men5321, def5870).
requisito(men5321, def5871).
requisito(men5321, eed5187).
requisito(men5321, eed5331).
requisito(men5321, men5603).
requisito(def5873, def5872).
requisito(def5873, men5321).
requisito(def5874, def5826).
requisito(men5322, def5872).
requisito(def5875, def5874).

nome(D, N) :- disciplina(D, _, N).

/* 1) O nome completo (N) de uma disciplina (com sigla D). */
nomecompleto(D, N) :- disciplina(D, _, N).

/* 2) Disciplinas (D1 e D2) que tem pre-requisito (PR) em comum */
precomum(D1, D2, PR) :- requisito(D1, PR), requisito(D2, PR).

/* 3) Disciplina (PR) que e pre-requisito de pre-requisito de uma disciplina D) */
prepre(D, PR) :- requisito(D, X), requisito(X, PR). 

/* 4) Disciplina (PR) que esta em uma determinada fase (F) e é pre-requisito de outra(s) disciplina(s). */
saopre(F, PR) :- fase(X, F), requisito(PR, X).

/* 5) Disciplina (D) que esta em uma determinada fase (F) e tem pre-requisito(s) para ser cursada */
tempre(F, D) :- fase(X, F), requisito(X, D).

/* 6) Disciplinas (D1 e D2) que estao em uma determinada fase (F), tem pre-requisito(s)
 em comum e sao pre-requisitos de outras disciplinas. */

temprecomumsaopre(F, D1, D2) :- requisito(D1, X), requisito(D2, X), requisito(Y, D1), requisito(Y, D2), fase(D1, F), fase(D2, F).

/* 7) Elabore uma questao que descubra uma disciplina (D) em uma determinada fase (F),
 a partir de criterios nao vistos anteriormente, e implemente sua resposta. */

proposta(F, D) :- nome(D, N), disciplina(_,F,N).
