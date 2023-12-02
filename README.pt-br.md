[![en](https://img.shields.io/badge/lang-en-red.svg)](https://github.com/Kauan231/Store-Management/blob/main/README.md)
[![pt-br](https://img.shields.io/badge/lang-pt--br-green.svg)](https://github.com/Kauan231/Store-Management/blob/main/README.pt-br.md)

# Store-Management

https://github.com/Kauan231/Store-Management/assets/63317471/693bfa36-8576-4aa2-8943-79012a86ee3c

Este projeto foi desenvolvido usando C++, [Mysql connector](https://dev.mysql.com/doc/dev/connector-cpp/latest/) e [Boost Libraries](https://www.boost.org/).

O sistema de Gerenciamento de Loja opera com uma divisão estruturada de responsabilidades entre o Gerente e o Vendedor, cada um equipado com opções específicas adaptadas aos seus papéis.

# **Capacidades do Gerente:**

- Visualizar uma lista abrangente de todos os funcionários.
- Adicionar ou Remover um Funcionário:
  - Durante a adição de um funcionário, o Gerente pode atribuir um nome e uma função (vendedor ou gerente). Posteriormente, o sistema gera um par único de nome de usuário e senha para o login do sistema do funcionário.
  - Ao remover um funcionário, o Gerente pode pesquisar pelo primeiro nome ou nome completo. O sistema fornece resultados de consulta com correspondências compatíveis, e se vários funcionários compartilharem o mesmo primeiro nome, o Gerente pode selecionar a opção desejada.
- Acessar um registro de todas as ações dos funcionários, detalhando vendas de produtos, adições, remoções ou reposições. Essas informações são registradas no banco de dados com carimbos de data e hora para cada ação.

# **Capacidades do Vendedor:**

- Visualizar uma lista abrangente de todos os produtos.
- Adicionar ou Remover um produto.
- Vender produtos: Itens selecionados para venda são adicionados ao carrinho. Ao concluir, todos os itens no carrinho são marcados como vendidos, e os detalhes da transação são registrados.
- Repor itens.

O sistema de login utiliza um par de nome de usuário e senha, verificado na tabela de login. Após a autenticação bem-sucedida, o sistema faz referência cruzada ao UUID do usuário com a tabela de funcionários para recuperar o nome e a função do funcionário logado. O perfil do funcionário é então armazenado em uma sessão, permitindo que o sistema apresente as opções apropriadas de Vendedor ou Gerente. Cada ação subsequente é registrada usando o UUID, indicando o tipo de ação (Vender, Adicionar, Repor, Remover), a quantia de cada produto e o valor de data e hora.

# **Estrutura do Banco de Dados:**

## **Tabelas:**

- **employees:** idEmployee (FK), nameEmployee, roleEmployee.

- **products:** idProduct (FK), nameProduct, AmountProduct.

- **login:** idUser (FK), username, password.

- **log:** idUser (FK), Ação, Quantidade, Hora.
