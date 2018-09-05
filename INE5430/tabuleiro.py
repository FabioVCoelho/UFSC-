class Nodo(object):
    # tamanho do tabuleiro
    tamanho = 5

    # matriz que representa o tabuleiro. Cada posicao
    # da matriz pode receber os valores 0 para representar
    # posicao vazia, 1 para representar posicao do pc e
    # 2 para representar posicao do jogador
    tabuleiro = [[]]

    # pontuacao final do tabuleiro
    pontuacao = 0

    # valor dos atributos alfa e beta utilizados
    # no algoritmo minimax
    alpha = 0
    beta = 0

    # pai deste nodo
    pai = 0

    # lista de filhos deste nodo
    filhos = []
    ult_posicao = {'x': 0, 'y': 0}

    # nodo pai
    def __init__(self, nodo, jogador):
        self.tabuleiro = [[0] * self.tamanho for i in range(self.tamanho)]
        self.pai = nodo
        self.gerarjogada(jogador)

    # durante o calculo da pontuacao, este nodo deve criar um de seus filhos
    # e esperar o retorno da pontuacao
    def minmax(self, nodo, jogador):
        self.gerarjogada(self, )
        return self.pontuacao

    # Nodo: Nodo pai deste nodo
    # jogador: true para o jogador, false para o PC
    def gerarjogada(self, jogador):

        # gera o tabuleiro desta jogada baseado nos parametros
        # enviados para a funcao. Para evitar de repetir uma jogada
        # utilizar a ult_pos para dar sequencia na criacao da
        # jogada. Utilize o algoritmo de rasterizacao
        # (iniciando da esquerda para a direita e de
        # cima para baixo). Nao esqueca de utilizar o nodo pai
        # para criar a jogada deste nodo a partir do estado
        # do tabuleiro do pai (jogada anterior a esta).
        # A posicao da ultima jogada gerada pode ser obtida
        # atraves da proprieda de do pai, self.pai.ult_posicao,
        # e está no formato: ult_pos['x'] e ult_pos['y']


        # se nao for nodo folha, pontuacao recebe heuristica
        if 0 == 0:
            self.pontuacao = self.heuristica
        #se for nodo folha, pontuacao recebe utilidade
        else:
            self.pontuacao = self.utilidade

        # ao final da geracao da jogada, o pai precisa ser
        # atualizado com a posicao da jogada que acabou de
        # ser gerada para que os proximos filhos do pai saibam
        # criar suas jogadas
        self.pai.ult_posicao = nova_posicao


    # Ao executar a heuristica ou a utilidade, armazenar a pontuacao
    # encontrada na variavel self.pontuacao, e retornar estes valores
    def heuristica(self):
        # calcula a pontuacao deste nodo e retorna
        return self.pontuacao

    def utilidade(self):
        # calcula a pontuacao deste nodo e retorna
        return self.pontuacao

    def efolha(self):
        print("decidir se é folha")
        return True

    def faltagerarfilhos(self):
        print("heuristica que define se falta gerar filhos "
              "para este nodo ou não")
        return True

    def printtabuleiro(self):
        for slots in self.tabuleiro:
            print(slots)

# metodos apenas para testes iniciais
# favor nao levar a serio
x = Nodo()
x.heuristica()