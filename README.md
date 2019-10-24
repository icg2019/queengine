# Jogo Cobrinha da Carlinha

O jogo da cobrinha eh pra disciplijna oo,jjbjbjbbgjbgj
e tem as seguintes funcionalidades
- 3 tipos de cobra (gfnskjgang)
- 5 tipos de frutas
- a cobra faz x coisa

# Como jogar

- A tecla *C* faz isso
- a tecla  *q* faz aueg


# Como instalar

Você precis ter instalado maquina virtual do java na seguinte configuraçao

``java 10.0.1 2018-04-17
Java(TM) SE Runtime Environment 18.3 (build 10.0.1+10)
Java HotSpot(TM) 64-Bit Server VM 18.3 (build 10.0.1+10, mixed mode)``

# Queengine

## Dependências

* libsdl2-dev
* libsdl2-image-dev
* libsdl2-ttf-dev
* libsdl2-mixer-dev

## Como executar a Queengine

**Obs:** Caso seja a primeira vez que esteja rodando, não é necessário o primeiro passo.

1. Primeiramente você deve rodar o seguinte comando:

```
make clean
```

2. Agora rode o comando para a criação da pasta **Build**:

```
make build
```

3. Execute o comando a seguir para compilar o projeto:

```
make comp
```

4. Por último, rode o comando para executar a engine:

```
make run
```

## Como utilizar a Queengine

### Primitvas

Para criar algum tipo de primitiva disponibilizada você deve utilizar as letras que estão destacadas após o nome de cada uma:

* Triângulo (**T**);
* Retângulo (**R**);
* Círculo (**C**).

Um dígito (1-9), em ordem crescente, será responsável por cada primitiva criada, seguindo a ordem de criação.

### Shaders

Para a aplicação do **shader** é necessário adicionar na **main** (engine/src/Main.cpp) cada um que deseja, em ordem de criação das primitivas. Ou seja, o primeiro _shader_ será aplicado à primeira primitiva criada, o segundo à segunda, etc.

## Como contribuir

Para contribuir com o projeto basta seguir os seguintes passos:

* Crie uma issue descrevendo uma feature que você queira trabalhar (ou olhe as issues já criadas);
* Desenvolva seu código, testes e documentação (caso necessário);
* Abra um pull request descrevendo as suas alterações propostas
* Seu pull request será revisado e analisado, podendo ser levantadas algumas questões para você sobre eventuais mudanças necessárias.

### License

Toda engine é desenvolvida sob a licença [GPL3](https://github.com/icg2019/queengine/blob/master/LICENSE).
