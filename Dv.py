# 1. Using NumPy:

# a. Create a 2D array with random values from 0 to 1 and compute mean, std deviation, and variance along the second axis.
import numpy as np
ARR1 = np.random.rand(4, 5)
mean = np.mean(ARR1, axis=1)
std_dev = np.std(ARR1, axis=1)
variance = np.var(ARR1, axis=1)

# b. Create a 2D array with user-defined dimensions and reshape it.
m, n = 4, 3  # Example dimensions
arr = np.random.randint(0, 100, size=(m, n))
reshaped_arr = arr.reshape(n, m)

# c. Test for zero, non-zero, and NaN elements in a 1D array.
arr_1d = np.array([0, 5, np.nan, 3, 0])
zero_indices = np.where(arr_1d == 0)[0]
non_zero_indices = np.where(arr_1d != 0)[0]
nan_indices = np.where(np.isnan(arr_1d))[0]

# d. Array operations and covariance/correlation calculations.
Array1 = np.random.rand(5)
Array2 = np.random.rand(5)
Array3 = np.random.rand(5)
Array4 = Array3 - Array2
Array5 = 2 * Array1
cov1 = np.cov(Array1, Array4)[0, 1]
corr1 = np.corrcoef(Array1, Array5)[0, 1]

# e. Sum and product calculations for array halves.
Array1 = np.random.rand(10)
Array2 = np.random.rand(10)
sum_first_half = np.sum(Array1[:5] + Array2[:5])
product_second_half = np.prod(Array1[5:] * Array2[5:])

# f. Memory size of an array.
random_arr = np.random.rand(5, 5)
memory_size = random_arr.nbytes

# g. Swap rows, reverse column in a 2D array.
arr_2d = np.random.randint(10, 100, (4, 4))
arr_2d[[0, 1]] = arr_2d[[1, 0]]  # Swap rows
reversed_col = arr_2d[:, ::-1]

# 2. Using Pandas Series:
import pandas as pd

# a. Create a series and sort.
series = pd.Series([5, 3, 8, 1, 2])
sorted_index = series.sort_index()
sorted_values = series.sort_values()

# b. Rank with duplicate values.
series_with_dupes = pd.Series([5, 3, 5, 1, 2])
rank_first = series_with_dupes.rank(method='first')
rank_max = series_with_dupes.rank(method='max')

# c. Index of min and max elements.
min_idx = series.idxmin()
max_idx = series.idxmax()

# 3. Using Pandas DataFrame:

# a. Generate data frame and replace 10% with NaN.
df = pd.DataFrame(np.random.rand(50, 3))
nan_indices = np.random.choice(df.size, int(df.size * 0.1), replace=False)
df.values.ravel()[nan_indices] = np.nan

# b. Identify and count missing values.
missing_count = df.isnull().sum()

# c. Drop column with >5 nulls.
df_dropped_col = df.dropna(axis=1, thresh=len(df) - 5)

# d. Drop row with max sum.
row_max_sum = df.sum(axis=1).idxmax()
df_dropped_row = df.drop(row_max_sum)

# e. Sort and remove duplicates.
df_sorted = df.sort_values(by=0)
df_no_duplicates = df_sorted.drop_duplicates(subset=0)

# f. Correlation and covariance.
corr = df[0].corr(df[1])
cov = df[1].cov(df[2])

# g. Discretize column.
df['binned'] = pd.cut(df[1], bins=5)

# 4. Using Excel data (replace file paths with actual paths):
workshop1 = pd.DataFrame({"Name": ["Alice", "Bob"], "Date": ["2024-01-01", "2024-01-02"], "Duration": [30, 40]})
workshop2 = pd.DataFrame({"Name": ["Alice", "Charlie"], "Date": ["2024-01-03", "2024-01-04"], "Duration": [50, 30]})

# a. Find common attendees.
common_attendees = pd.merge(workshop1, workshop2, on='Name')

# b. Single workshop attendees.
all_attendees = pd.concat([workshop1, workshop2])
single_workshop = all_attendees.drop_duplicates(subset='Name', keep=False)

# c. Row-wise merge and total records.
merged_df = pd.concat([workshop1, workshop2], axis=0)

# d. Multi-index descriptive statistics.
merged_df.set_index(['Name', 'Date'], inplace=True)
descriptive_stats = merged_df.describe()

# 5. Using Iris dataset:
iris_data = pd.DataFrame({"SepalLength": [5.1, 4.9], "SepalWidth": [3.5, 3.0], "PetalLength": [1.4, 1.4], "PetalWidth": [0.2, 0.2], "Class": ["Iris-setosa", "Iris-versicolor"]})

# a. Load data and check info.
iris_info = iris_data.info()

# b. Check missing values.
missing_values = iris_data.isnull().sum()

# c. Plot bar chart for class frequency.
iris_data['Class'].value_counts().plot(kind='bar')

# d. Scatter plot with regression line.
iris_data.plot.scatter(x='PetalLength', y='SepalLength')

# e. Density plot for PetalWidth.
iris_data['PetalWidth'].plot(kind='density')

# f. Pairplot (requires seaborn).
import seaborn as sns
sns.pairplot(iris_data, hue='Class')

# g. Heatmap for numeric attributes.
sns.heatmap(iris_data.corr(), annot=True)

# 6. Using Titanic dataset:
titanic_data = pd.DataFrame({"Age": [22, 38], "Fare": [7.25, 71.28], "Class": ["3rd", "1st"], "Survived": [0, 1]})

# a. Clean data by dropping column with most missing values.
titanic_data = titanic_data.dropna(axis=1)

# b. Count passengers over 30.
passengers_over_30 = titanic_data[titanic_data['Age'] > 30].shape[0]

# c. Total fare for second class.
total_fare_2nd_class = titanic_data[titanic_data['Class'] == '2nd']['Fare'].sum()

# d. Compare survivors by class.
survivors_by_class = titanic_data.groupby('Class')['Survived'].sum()

# e. Descriptive stats for age by gender.
# Add gender data for complete example.

# f. Scatter plot for fare by gender.
# Add gender data for plotting.

# g. Density comparison for age and fare.
# Add density plot.

# 7. Family income data frame:
family_data = pd.DataFrame({
    "FamilyName": ["Shah", "Vats", "Vats", "Kumar", "Vats", "Kumar", "Shah", "Shah", "Kumar", "Vats"],
    "Gender": ["Male", "Male", "Female", "Female", "Female", "Male", "Male", "Female", "Female", "Male"],
    "MonthlyIncome": [44000, 65000, 43150, 66500, 255000, 103000, 55000, 112400, 81030, 71900]
})

# a. Family-wise gross monthly income.
gross_income = family_data.groupby('FamilyName')['MonthlyIncome'].sum()

# b. Highest and lowest income for each family.
high_low_income = family_data.groupby('FamilyName')['MonthlyIncome'].agg(["max", "min"])

# c. Income less than 80,000.
income_below_80k = family_data[family_data['MonthlyIncome'] < 80000]

# d. Count and average income of females.
female_data = family_data[family_data['Gender'] == 'Female']
total_females = female_data.shape[0]
average_female_income = female_data['MonthlyIncome'].mean()

# e. Remove rows below average income.
average_income = family_data['MonthlyIncome'].mean()
filtered_data = family_data[family_data['MonthlyIncome'] >= average_income]
