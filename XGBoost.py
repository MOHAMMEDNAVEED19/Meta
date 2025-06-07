# ad_performance_xgboost.py
import xgboost as xgb
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error

# Sample dataset: CTR, time, age_group → ROI
data = {
    'ctr': [0.1, 0.3, 0.05, 0.2, 0.4],
    'time_of_day': [10, 14, 20, 9, 18],
    'age_group': [25, 30, 22, 40, 35],
    'roi': [20, 60, 10, 40, 80]
}

df = pd.DataFrame(data)
X = df[['ctr', 'time_of_day', 'age_group']]
y = df['roi']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)
model = xgb.XGBRegressor()
model.fit(X_train, y_train)

preds = model.predict(X_test)
print("MSE:", mean_squared_error(y_test, preds))
