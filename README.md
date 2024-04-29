**Descrição do problema:**

Suponha que você tenha um programa que simula uma fila de pessoas esperando para usar um caixa eletrônico. Existem várias threads representando pessoas que chegam à fila para usar o caixa eletrônico. No entanto, o caixa eletrônico só pode ser usado por uma pessoa de cada vez. Portanto, as pessoas devem esperar na fila até que seja sua vez de usar o caixa eletrônico.

*Implementação da função espera_na_fila:*

  * A função 'espera_na_fila' representa uma pessoa esperando na fila quando o caixa eletrônico está ocupado.
  * Dentro da função, a pessoa é adicionada à fila, e a variável 'pessoa_na_fila' é definida como 1 para indicar que há pessoas na fila.
  * Após esperar um tempo aleatório, a função é encerrada.
    
*Implementação da função uso_caixa:*

  * A função 'uso_caixa' representa uma pessoa usando o caixa eletrônico.
  * Dentro da função, a pessoa espera até que haja alguém na fila (pessoa_na_fila == 1) e o caixa esteja livre (usando_caixa == 0).
  * Quando é sua vez de usar o caixa, a pessoa marca o caixa como ocupado (usando_caixa == 1), imprime uma mensagem indicando que está usando o caixa, aguarda um tempo aleatório (simulando o uso do caixa) e, em seguida, marca o caixa como liberado (usando_caixa == 0).
    
*Sincronização entre as Threads:*

  * O acesso ao caixa eletrônico é protegido por um mutex (mutex). Isso garante que apenas uma thread por vez execute a seção crítica do código, evitando condições de corrida.
  * São usadas duas variáveis de condição (pessoas_aguardando_cond e caixa_liberado_cond) para sincronizar o acesso ao caixa eletrônico. As threads esperam nessas variáveis de condição quando não podem prosseguir com sua operação.
