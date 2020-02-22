import time
import numpy as np

def _t(x):
     return np.transpose(x)


def _m(A, B):
     return np.matmul(A, B)


# 동적 프로그램에서 연산 반복을 피하기 위해 값을 저장하고 불러다 쓸수 있도록
# 메모리를 잡기 위해서 시그모이드를 클래스로 구성

class Sigmoid:
     def __init__(self):
          self.last_o = 1
# 마지막 출력을 저장해놓으면 나중에 grd()를 계산할 때 사용할 수 있다.
# 곱하기 형식으로 grad()가 실행되기 때문에 0으로 놓으면 안돼니까 1로 설정

     def __call__(self, x):
          self.last_o = 1 / (1.0 + np.exp(-x))
          return self.last_o

     def grad(self):  # sigmoid(x)(1-sigmoid(x)) 시그모이드 함수의 미분
          return self.last_o * (1 - self.last_o)


# Sigmoid가 call되고 나서 grad() call되면 현제 gradient가 리턴된다.

class MeanSquaredError:
     def __init__(self):
          # gradient
          self.dh = 1
          self.last_diff = 1

     def __call__(self, h, y):  # 1/2 * mean ((h - y)^2) # h: 출력 y: 정답
          self.last_diff = h - y
          return 1 / 2 * np.mean(np.square(h - y))

     def grad(self):  # h - y
          return self.last_diff


class Neuron:
     def __init__(self, W, b, a_obj): # Model parameters
          self.W = W
          self.b = b
          self.a = a_obj() # 객체 a를 함수라고 선언하는 것일까? ???
# activation  f'n에 해당, 이것도 시그모이드 클래스처럼 클래스 형식으로 들어올 것이기 때문에
# 인스탄스를 생성해준다.

          # gradient
          self.dW = np.zeros_like(self.W)
          self.db = np.zeros_like(self.b)
          self.dh = np.zeros_like(_t(self.W))

          self.last_x = np.zeros((self.W.shape[0]))
          self.last_h = np.zeros((self.W.shape[1]))
          # 이전 입력 값을 갖고 있어야 미분가능

     def __call__(self, x):
          self.last_x = x
          self.last_h = _m(_t(self.W), x) + self.b
          return self.a(self.last_h)  # activation f'n 까지 고려

     def grad(self):  # 역전파 학습에서 이전 입력 h(n-1)로 미분 dy/dh = W
          return self.W * self.a.grad()  # 예를 activation gradient 라고 한다.

     def grad_W(self, dh):
          grad = np.ones_like(self.W)
          grad_a = self.a.grad()
          for j in range(grad.shape[1]):  # dy/dw = x
               grad[:, j] = dh[j] * grad_a[j] * self.last_x
          return grad

     def grad_b(self, dh):  # dy/dh = 1, dh: 지금까지 넘어온 놈의 그래디언트
          return dh * self.a.grad()


class DNN:  # 기존 방법과 동일
     def __init__(self, hidden_depth, num_neuron, input, output, activation=Sigmoid):
          def init_var(i, o):
               return np.random.normal(0.0, 0.01, (i, o)), np.zeros((o,))

          self.sequence = list()
          # First hidden layer
          W, b = init_var(input, num_neuron)
          self.sequence.append(Neuron(W, b, activation))

          # Hidden Layers
          for index in range(hidden_depth):
               W, b = init_var(num_neuron, num_neuron)
               self.sequence.append(Neuron(W, b, activation))

          # Output Layer
          W, b = init_var(num_neuron, output)
          self.sequence.append(Neuron(W, b, activation))

     def __call__(self, x):
          for layer in self.sequence:
               x = layer(x)
          return x

     def calc_gradient(self, loss_obj):  # 이부분은 새롭게 생긴부분
          loss_obj.dh = loss_obj.grad()  # dh 가 모두 그라디언트
          self.sequence.append(loss_obj)

          # back-prop loop
          for i in range(len(self.sequence) - 1, 0, -1):  # 역순으로..
               l1 = self.sequence[i]
               l0 = self.sequence[i - 1]

               l0.dh = _m(l0.grad(), l1.dh)
               l0.dW = l0.grad_W(l1.dh)
               l0.db = l0.grad_b(l1.dh)

          self.sequence.remove(loss_obj)


def gradient_descent(network, x, y, loss_obj, alpha=0.01):
     loss = loss_obj(network(x), y)  # Forward inference 순방향 추론
     network.calc_gradient(loss_obj)  # Back-propagation  역전파 학습

     for layer in network.sequence:
          layer.W += -alpha * layer.dW
          layer.b += -alpha * layer.db
     return loss


# Test
x = np.random.normal(0.0, 1.0, (10,))
y = np.random.normal(0.0, 1.0, (2,))

t = time.time()
dnn = DNN(hidden_depth=5, num_neuron=32, input=10, output=2, activation=Sigmoid)
loss_obj = MeanSquaredError()
for epoch in range(100):
     loss = gradient_descent(dnn, x, y, loss_obj, alpha=0.01)
     print('Epoch {}: Test loss {}'.format(epoch, loss))
print('{} seconds elapsed.'.format(time.time() - t))
