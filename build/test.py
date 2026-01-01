import quant_engine
import time

# 1. Define Market Parameters
# Spot=100, Strike=100, Risk-free=5%, Volatility=20%, T=1 year
S0, K, r, sigma, T = 100.0, 100.0, 0.05, 0.2, 1.0

print(f"Market: S={S0}, K={K}, r={r}, sigma={sigma}, T={T}")
print("-" * 50)

# 2. Initialize the C++ Model
model = quant_engine.BSModel(S0, K, r, sigma, T)

# 3. Price a Call Option (using 1 million simulations)
start = time.time()
call_price = model.price_option(1_000_000, quant_engine.OptionType.Call)
end = time.time()

print(f"Call Price: {call_price:.6f}")
print(f"Time Taken: {(end - start)*1000:.2f} ms")