# Calculator
#### Usage
This calculator takes an input like "1 + 6 * 3 - 2" and produces "17".

`> make run` or

`> echo "1 + 6 * 3 - 2" | make run`

#### Design
The model of this code is similar to the model of a compiler front end because, after all, a calculator is like a very tiny interpreter. It takes a simpl mathematical expression (source program) and passes it through a lexical analyzer to produce meaningful tokens. The tokens are then passed through a parser that builds a syntax tree that represents the expression. Finally, there is an evaluater function that traverses the syntax tree to produce a result.
