# Calc

Similar to UNIX BC (not really).

## Usage

You can clone normally or with the `--recursive` flag to pull submodules.

Build with `make`, clean buildspace with `make clean`.

Enter the shell using `bin/calc`.

## Documentation 

### Operators

| Name | Definition | Description |
| --- | --- | --- |
| `-x` | $ -x$ | Negation |
| `a = b` | $ a = b$ | Set $a$ equal to $b$ |
| `a + b` | $ a + b$ | Addition |
| `a - b` | $ a - b$ | Subtraction |
| `a * b` | $ ab$ | Multiplication |
| `a / b` | $ \frac{a}{b}$ | Division |
| `a ^ b` | $ a^{b}$ | Exponentiation |
| `a % b` | $ a\mod{b}$ | Modulous |

### Variables 
| Name | Definition | Description |
| --- | --- | --- |
| `_` | default to $ 0 $ | Result of previous expression |
| `pi` | $ \pi = 3.14159...$ | Constant representing PI |
| `e` | $ e = 2.71828...$ | Constant representing Euler's number |
| `h_deriv` | $ 10^{-7} $ | Infintecimal constant for `nderiv` |
| `h_integ` | $ 10^{-5} $ | Infintecimal constant for `ninteg` |

### Functions
| Name | Definition | Description |
| --- | --- | --- |
| `abs(x)` | $ \|x\| $ |  |
| `sqrt(x)` | $ \sqrt{x} $ |  |
| `ln(x)` | $ \ln{x} $ |  |
| `ln(x, b)` | $ \log_{b}{x} $ |  |
| `exp(x)` | $ e^{x} $ |  |
| `floor(x)` | $ \lfloor{x}\rfloor $ |  |
| `ceil(x)` | $ \lceil{x}\rceil $ |  |
| `round(x)` | $ \lfloor{x}\rceil $ |  |
| `max(a, b)` | $ a \wedge b $ | Maximum of $a$ and $b$ |
| `min(a, b)` | $ a \vee b $ | Minimum of $a$ and $b$ |
| `sin(θ)` | $ sin(\theta) $ | |
| `cos(θ)` | $ cos(\theta) $ | |
| `tan(θ)` | $ tan(\theta) $ | |
| `asin(x)` | $ sin^{-1}(x) $ | |
| `acos(x)` | $ cos^{-1}(x) $ | |
| `atan(x)` | $ tan^{-1}(x) $ | |
| `sinh(x)` | $ \frac{e^{x} - e^{x}}{2} $ | Hyperbolic sine |
| `cosh(x)` | $ \frac{e^{x} + e^{x}}{2} $ | Hyperbolic cosine|
| `tanh(x)` | $ \frac{e^{x} - e^{x}}{e^{x} + e^{x}} $ | Hyperbolic tangent |
| `hypot2(a, b)` | $ \sqrt{a^2 + b^2} $ | |
| `hypot3(a, b, c)` | $ \sqrt{a^2 + b^2 + c^2} $ | |
| `nderiv(f, x, n)` | $ {\frac{df}{dx} \rvert_{x=n} } $ | Derivative at $n$|
| `ninteg(f, x, a, b)` | $ {\int_{a}^{b}{fdx}} $ | Definite integral from $a$ to $b$ |