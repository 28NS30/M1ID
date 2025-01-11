# Mi1D (kind of)
## Motivation
The goal of this project will be to learn as much as I can and try out all sorts of different models. 
The end goal of Model In 1 Day would be to perform well in a competition like HiMCM or Kaggle. 
Although the project is named Mi1D, I will not be holding myself to the time limitations very strictly, 
as it's mostly a learning experience. All the projects will be using C++ and will reduce the number of libraries as
much as possible. The purpose of this is to create all sorts of models from SCRATCH. No libraries (with a few 
exceptions). No ChatGPT code. Just plain old C++ that I wrote. Shouted to Jared for encouraging me to start this project.

## 1. Linear Reggression Model

#### Purpose
I originally set out to create a general linear regression model that could easily be repurposed or used as a skeleton for a future project. A pretty big
driving motivation for this project was just to beat Jared in the Kaggle Comp😅.

#### Description
Pretty self-explanatory. I created a linear regression model and tested it 
with the [Titanic Kaggle Challenge](https://www.kaggle.com/competitions/titanic/data?select=test.csv). For the training, I used
using a batch gradient descent algorithm. I can effectively minimize the loss by calculating the gradient of the loss function (MSE) with respect to a weight every epoch, and then stepping in the opposite direction. Then, to further improve my model, I added some interaction terms and some squared terms to get
a better fit.

#### Results
I am not so satisfied with the final fit using the model, so I will probably revisit this later for further optimization. After tweaking many different parameters and fixing bugs, I ended up with a mean squared error of 0.2068. Not bad, but could definitely be better. Although I did test a few different
cutoffs for the final output of the model, since the titanic problem requires a binary output, given more time, I would try to implement some more elements of
logistical regression. The model could also have improved if I had time to tweak more with the inputs and perhaps try imputation or data cleaning. All in all, I'm pretty happy with the outcome of this model, but will probably just move on for now.
