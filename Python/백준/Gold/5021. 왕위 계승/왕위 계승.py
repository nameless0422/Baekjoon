import sys

input = sys.stdin.readline

n, m = map(int, input().split())
sunjo = input().strip()

# 자식 -> (부모1, 부모2)
parents = {}

# 후보들
people = set([sunjo])  # 등장 인물들 모아두면 optional로 좋음
for _ in range(n):
  child, p1, p2 = input().split()
  parents[child] = (p1, p2)
  people.add(child)
  people.add(p1)
  people.add(p2)

claimants = [input().strip() for _ in range(m)]
for c in claimants:
  people.add(c)

# 메모이제이션: 이름 -> 창건자 혈통 비율(0.0 ~ 1.0)
blood = {}


def get_blood(name: str) -> float:
  # 이미 계산됨
  if name in blood:
    return blood[name]
  # 창건자는 1.0
  if name == sunjo:
    blood[name] = 1.0
    return 1.0
  # 부모 정보가 없으면 0
  if name not in parents:
    blood[name] = 0.0
    return 0.0
  p1, p2 = parents[name]
  val = 0.5 * get_blood(p1) + 0.5 * get_blood(p2)
  blood[name] = val
  return val


# 각 후보의 혈통 비율을 계산하여 최댓값 선택
best_name = None
best_val = -1.0
for name in claimants:
  val = get_blood(name)
  if val > best_val:
    best_val = val
    best_name = name

print(best_name)
