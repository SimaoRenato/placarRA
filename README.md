# placarRA
Código principal do Arduino: painel.ino
código do ESP 32: wifiReceiver.ino

Arquivos Excel são para facilitar criação de biblioteca de bandeiras

Visão geral de operação:

O arduino cria uma conexãos com o servidor TCP que é criado no sistema de cronometragem. A conexão física é feita através do Wifi e a definição da senha de wifi deve ser feita no ESP 32

Ao receber o comando do servidor o arduino interpreta e exibe a mensagem.

