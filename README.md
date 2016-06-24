# Calculator
#### Usage
This calculator takes an input like `1 + 6 * 3 - 2` and produces `17`.

`> make run` or

`> echo "1 + 6 * 3 - 2" | make run`

#### Design
The model of this code is similar to the model of a compiler front end because, after all, a calculator is like a very tiny interpreter. It takes a simple mathematical expression (source program) and passes it through a lexical analyzer to produce meaningful tokens. The tokens are then passed through a parser that builds a syntax tree that represents the expression. Finally, there is an evaluater function that traverses the syntax tree to produce a result.

#### Code Flow
![calculator_flowchart](https://cloud.githubusercontent.com/assets/2036765/16347369/339e5f38-3a01-11e6-8c06-51f60a62df10.png)

##### Scanner
The scanner needs the input expression to be space separated since it is using `strsep` to break the expression into tokens. It then aliases the tokens with unique integer values.

##### Parser
The parser taken the list of tokens as input and builds a syntax tree. The syntax tree is represented in memory by a linked list of structs that form a binary tree like so:
```
struct Node {
  int value;
  struct Node* lchild;
  struct Node* rchild;
};
```

##### Evaluator
The evaluator recursively walks the syntax tree evaluating each node.
