import sys
MOD = 10007
N, K = map(int, sys.stdin.readline().split())

dp = [0] * (K + 1)
dp[0] = 1  # nC0 = 1

for i in range(1, N + 1):
    up = min(i, K)
    for k in range(up, 0, -1):
        dp[k] = (dp[k] + dp[k - 1]) % MOD

print(dp[K])
