# CS380 – Artificial Intelligence for Games  
## Deep Q-Learning Snake AI

This project implements a **Deep Reinforcement Learning agent** using **Deep Q-Learning (DQN)** to learn how to play the classic **Snake** game.

The goal of the project is to explore practical game AI techniques by combining **Neural Networks** and **Reinforcement Learning**, focusing on learning through interaction with the environment rather than scripted behavior.

---

## Project Overview

- **AI Technique:** Deep Q-Learning (DQN)
- **Environment:** Snake game
- **Language:** C++
- **Context:** Academic project for CS380 – Artificial Intelligence for Games (DigiPen Institute of Technology)

The AI learns to play Snake by:
- Observing the game state
- Selecting actions using an epsilon-greedy policy
- Receiving rewards and penalties based on its behavior
- Improving over time through experience replay

Learning starts immediately when the program is executed.

---

## Core AI Components

### Neural Network
- Multi-layer perceptron
- Used to approximate the Q-function
- Trained using forward and backward propagation
- Sigmoid activation function

### Deep Q-Learning
- Combines Q-Learning with a neural network
- Uses:
  - Main network
  - Target network
- Implements:
  - Bellman update
  - Experience replay buffer
  - Epsilon decay (exploration → exploitation)

### Experience Replay
- Stores past experiences (state, action, reward, next state)
- Trains the network on previous experiences to improve stability and learning consistency

---

## Controls & UI

- The AI starts learning automatically when the program runs
- A **speed slider** is available in the top-left corner of the window
- The initial speed is set high to accelerate learning
- Speed automatically decreases as the experience buffer grows

---

## Build & Run

- **IDE:** Visual Studio
- **Recommended configuration:** Release  
  *(Debug mode is significantly slower due to the amount of computation)*

---

## Code Structure

The main implementation can be found in:

Source/NeuralNetwork/
├── NeuralNetwork.h
└── NeuralNetwork.cpp


Key areas include:
- Neural network implementation
- Deep Q-Learning logic
- Experience replay buffer
- Parameter initialization

### Tweaking Learning Parameters

Deep Q-Learning parameters can be modified in:

```cpp
Q_Learning::Initialize()
```
Located in:

Source/NeuralNetwork/NeuralNetwork.cpp
(approx. lines 543–601)

Changing these values allows experimentation with different learning behaviors.

---

## Results & Notes

- Learning behavior may vary between runs due to initial randomness
- Multiple executions are recommended to observe different learning patterns
- Two example videos are included showing early and later stages of training

---

## Known Limitations

- Learning performance is sensitive to parameter tuning
- Early training stages may appear unstable due to exploration

---

## Notes

This is an academic project.  
Only original implementation code is included; assignment specifications and teaching materials are not reproduced verbatim.
