import streamlit as st
import pandas as pd
import numpy as np
from datetime import datetime, time
from sklearn.linear_model import LinearRegression
import matplotlib.pyplot as plt

# Title of the web app
st.title('Delivery Prediction Model')

# Instructions
st.write("This app predicts the possibility of deliveries based on the temperature during a specific date and time slot.")

# File uploader allows user to add their own CSV
uploaded_file = st.file_uploader("Upload your input CSV file", type=["csv"])

# Date and time slot input
date_input = st.text_input("Enter the date (YYYY-MM-DD):")
time_slot = st.text_input("Enter the time slot (HH:MM-HH:MM):")

# Function to process CSV and predict temperature
def process_and_predict(uploaded_file, date_input, time_slot):
    df = pd.read_csv(uploaded_file)
    df = df.pivot(index='time', columns='measure_name', values='measure_value').reset_index()
    df['time'] = pd.to_datetime(df['time'])
    df.set_index('time', inplace=True)
    # Check if 'temperature' is in the pivoted columns, otherwise raise an error
    if 'temperature' not in df.columns:
        raise ValueError("'temperature' column not found. Check the CSV format.")
    df['Temp_lag'] = df['temperature'].shift(1)
    df.dropna(inplace=True)

    # Fit Linear Regression Model
    X = df[['Temp_lag']]
    y = df['temperature']
    ts_model = LinearRegression()
    ts_model.fit(X, y)
    df['predicted_temperature'] = ts_model.predict(X)
    
    # Parse the date and time slot
    date = pd.to_datetime(date_input)
    start_time, end_time = time_slot.split('-')
    start_hour, start_minute = map(int, start_time.split(':'))
    end_hour, end_minute = map(int, end_time.split(':'))

    # Create a mask for the datetime index
    date_mask = (df.index.date == date.date()) & \
                (df.index.time >= time(start_hour, start_minute)) & \
                (df.index.time <= time(end_hour, end_minute))

    # Filter the DataFrame
    df_filtered = df.loc[date_mask]

    # Predict delivery status based on a dummy threshold
    delivery_possible = df_filtered['predicted_temperature'].between(15, 25).all()
    
    return delivery_possible, df_filtered

# Main app logic
if uploaded_file and date_input and time_slot:
    try:
        delivery_possible, df_filtered = process_and_predict(uploaded_file, date_input, time_slot)
        
        # Display prediction result
        if delivery_possible:
            st.success("Delivery is predicted in this time slot based on the temperature.")
        else:
            st.error("Delivery is not predicted in this time slot based on the temperature.")
        
        # Plot actual vs predicted temperatures
        fig, ax = plt.subplots()
        ax.plot(df_filtered.index, df_filtered['temperature'], label='Actual Temperature', color='blue')
        ax.plot(df_filtered.index, df_filtered['predicted_temperature'], label='Predicted Temperature', linestyle='--', color='red')
        ax.set_title('Actual vs Predicted Temperatures')
        ax.set_xlabel('Time')
        ax.set_ylabel('Temperature')
        ax.legend()
        st.pyplot(fig)
    except Exception as e:
        st.error(f"An error occurred: {e}")

else:
    st.warning('Please upload a CSV file, enter a date, and enter a time slot.')
