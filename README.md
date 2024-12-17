# Mi1D
## Purpose
The goal of this project will be to learn as much as I can and try out all sorts of different models. 
The end goal of Model In 1 Day would be to perform well in a competition like HiMCM or Kaggle. 
Although the project is named Mi1D, I will not be holding myself to the time limitations very strictly, 
as it's mostly a learning experience. All the projects will be using C++ and will reduce the number of libraries as
much as possible. The purpose of this is to create all sorts of models from SCRATCH. No libraries (with a few 
exceptions). No ChatGPT code. Just plain old C++ that I wrote. Shouted to Jared for encouraging me to start this project.

## 1. Linear Reggression Model

#### Description
Pretty self-explanatory. I created a linear regression model and tested it 
with the [Titanic Kaggle Challenge](https://www.kaggle.com/competitions/titanic/data?select=test.csv). For the training, I used
using a batch gradient descent algorithm. By calculating the gradient of the loss function (MSE) with respect to a weight every epoch, and then stepping
in the opposite direction, I can effectively minimize the loss. Then, to further improve my model, I added some interaction terms and some squared terms to get
a better fit.

#### Results
