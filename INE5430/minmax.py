from .tabuleiro import Nodo


def minmax(nodo, jogador, profundidade):
    if nodo.efolha():
        return nodo.utilidade()
    elif profundidade <= 0:
        return nodo.heuristica()

    beta = -99999999
    alfa = 99999999

    while nodo.faltagerarfilhos():
        nodo_atual = Nodo(nodo, not jogador)
        pontuacao = minmax(nodo_atual, not jogador, profundidade-1)

        if jogador:
            if beta > pontuacao:
                beta = pontuacao
                if alfa > beta:
                    return beta
        else:
            if alfa < pontuacao:
                alfa = pontuacao
                if alfa > beta:
                    return alfa

    if jogador:
        return beta
    else:
        return alfa

# indeciso de quem deveria ter a pontuação da jogada, se a prórpria jogada ou o tabuleiro da jogada
# aonde guardar a jogada que foi feita? em uma classe Jogada, onde ficaria a linha e coluna utilizadas?
# por definição, jogador true é IA e false é pessoa?

# A pontuacao da jogada vai ser do nodo, que tera a pontuacao real
# A jogada vai ser guardada dentro do nodo, na na matriz tabuleiro
# Defini que jogador eh True e IA eh False, dessa forma pode-se simplesmente dizer: "if jogador:"
# que eh o mesmo que dizer: "if jogador == True", fica mais legivel