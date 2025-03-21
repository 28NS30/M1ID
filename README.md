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


## 2. Neural Network

#### Purpose
I've always really reaaaallly wanted to train a reinforcement learning model to play a game, so this seemed like the natural first step. For this model, I definitely wasn't going to do it in 1 day. Over a month or so, I learned about NNS and built one. From scratch. No libraries. No chatgpt. And way too much time. 

#### Description
With nothing but a dream 💭 I just wanted to make a neural network. For simplicity's sake, I didn't choose to make it a class, I just had global variables. Throughout the building of this
model, I had to learn calculus. Lowkey not that hard. The model will calculate the gradient of the loss function with respect to the pre-activation (z) of each node then propagate it backward for the gradient calculation of each node. Then it simply updates each weight. Really cool stuff (or at least I think it is).

#### Results
I'm pretty satisfied with the model, I tested it a few times. It passed the XOR test which I found pretty cool and it just works. I think there are quite a few next steps/improvements for
this model. At some point in the hopefully not-so-distant future, I want to rewrite/adapt it into OOP and wrap it all in a neural network class. I also want to maybe leverage some libraries
or cpp threading to improve the performance speed with matrix multiplication. Once I'm satisfied with Neural Network, I think I might start to either apply it for some modeling problems, 
branch it into something reinforcement learning related, or perhaps have it play a game. I definitely learned quite a bit from this project and it was quite interesting.

## 3. SIR Models

#### Purpose
The purpose of this project is to model the spread of a disease through –I guess– the world. I actually implemented 2 different-ish ones that build upon each other. The first was to use a basic SIR model to model the number of Suscetible, Infected, and Recovered/Dead people. Then I adapted the model to put into consideration the number of people exposed, transitioning it into a SEIR model.

#### Description
The model is suprisingly simple and kind of just works iteratively. There isn't exactly any ml in this, but I still found it pretty interesting. Honestly a really really easy model. The model works by using predefined constants to determine the rate at which people move from group to group. This model isn't so much technically difficult –or rather not at all– but is suprisingly good at predicting/modeling disease outbreaks given the right research.

#### Results
I'm not gonna lie this was incredibly underwhelming. I thought it was going to be really cool but it was really just a loop. There are some modifications I could apply to make it more interesting. For example, by adding in a bit of randomness into the model, I could make it stochastic or perhaps into a Monte Carlo simulation. However I'm just really sick of this thing –pun intended– and I want to move on. This model marks a bit of a pivot in my journey. Before this I was just doing general models that I thought (and still think) are cool, but moving forward, I think I'll try to be a bit more structured and actually start working away at some of the ideas I have listed.
