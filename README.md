Este projeto implementa uma tabela hash em C para gerenciamento de usuários e senhas, utilizando endereçamento linear para tratamento de colisões.

📋 Descrição
O sistema permite:

Cadastrar novos usuários com senha

Fazer login verificando usuário e senha

Remover usuários existentes

Visualizar o estado completo da tabela hash

Tratamento de colisões com endereçamento linear

Reutilização de espaços removidos

📝 Como usar
Inicialização: Ao executar, informe o tamanho desejado para a tabela hash

Menu de opções:

1 - Cadastrar usuário: Insere novo usuário e senha

2 - Login: Verifica credenciais de usuário

3 - Remover usuário: Remove um usuário existente

4 - Mostrar tabela: Exibe o estado completo da tabela

5 - Sair: Encerra o programa


🔧 Funcionalidades implementadas
Conversão de string para inteiro: Função que transforma strings em valores numéricos

Função hash: Distribuição uniforme usando módulo

Inserção: Com tratamento de colisões e reutilização de espaços

Busca: Localização eficiente de usuários

Remoção: Marcação lógica com possibilidade de reutilização

Login: Verificação de usuário e senha

Visualização: Impressão completa do estado da tabela

📊 Exemplo de uso
text
Informe o tamanho da tabela hash: 10

Menu:

1 - Cadastrar usuario

2 - Login

3 - Remover usuario

4 - Mostrar tabela

5 - Sair

Opcao: 1

Usuario: joao

Senha: 123456

Usuario cadastrado.
