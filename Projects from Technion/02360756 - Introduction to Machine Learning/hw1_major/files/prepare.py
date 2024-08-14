import pandas as pd
from sklearn.preprocessing import MinMaxScaler, StandardScaler


def prepare_data(training_data, new_data):
  # Create a copy of the new data to transform
  prepared_data = new_data.copy()

  # Replace missing values in 'household_income' with the median of the training data
  median_household_income = training_data['household_income'].median()
  prepared_data['household_income'].fillna(median_household_income, inplace=True)

  # Check if the 'blood_type' column is present
  if 'blood_type' in prepared_data.columns:
    # Create the 'SpecialProperty' feature before dropping 'blood_type'
    prepared_data['SpecialProperty'] = prepared_data['blood_type'].isin(['O+', 'B+'])
    prepared_data.drop(columns=['blood_type'], inplace=True)

  min_max_pcr_features = ['PCR_03', 'PCR_10']
  standard_pcr_features = ['PCR_01', 'PCR_02', 'PCR_04', 'PCR_05', 'PCR_06', 'PCR_07', 'PCR_08', 'PCR_09']

  # Min-Max normalization for PCR_03 and PCR_10
  scaler1 = MinMaxScaler(feature_range=(-1, 1))
  scaler1.fit(training_data[min_max_pcr_features])
  prepared_data[min_max_pcr_features] = scaler1.transform(prepared_data[min_max_pcr_features])

  # Standardization for the other PCR features
  scaler2 = StandardScaler()
  scaler2.fit(training_data[standard_pcr_features])
  prepared_data[standard_pcr_features] = scaler2.transform(prepared_data[standard_pcr_features])

  return prepared_data
