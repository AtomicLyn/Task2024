import pandas as pd
import seaborn as sns
from matplotlib import pyplot as plt
from scipy import stats

df = pd.read_excel("data_1.xlsx")
print(df)

print("1. Нормализуем все данные. Скалируем все данные в диапозоне от -1 до 1")
df_min = df.min()
df_max = df.max()
df = (df - df_min)/(df_max - df_min) * 2 - 1
print(df)

print("2. Обрабатываем пропуски. Обрабатываем выбросы.")
df = df.dropna()
z_scores = df.apply(stats.zscore)
df = df[(z_scores < 3).all(axis=1)]
print(df)
sns.boxplot(df)
plt.show()

print("3. Строим матрицу корреляции.")
corr = df.corr()
print(corr)
sns.heatmap(corr)
plt.show()

print("4. Строим гистограммы распределения")
df.hist()
plt.show()

print("5. Ищем (взаимозависимые данные)")
for col in corr.columns:
    check_columns = [c for c in corr.columns if corr.at[col, c] < 0.5]
    dependent_data = corr[col].drop(col).drop(check_columns)
    dependent_names = dependent_data.index.tolist()
    print(f"{col} - {dependent_names}")

print("6. Тест на нормальность")
for col in df.columns:
    _, p_val = stats.normaltest(df[col])
    if p_val > 0.05:
        print(f"{col} = нормальное ({p_val})")
    else:
        print(f"{col} = не нормальное ({p_val})")

