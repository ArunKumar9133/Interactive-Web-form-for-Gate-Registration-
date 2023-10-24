from flask import Flask, request
from flask_cors import CORS
import pandas as pd

app = Flask(__name__)
CORS(app)

@app.route('/submit_registration', methods=['POST'])
def submit_registration():
    data = request.json

    # Load existing Excel file or create a new one
    try:
        df = pd.read_excel('form_data.xlsx')
    except FileNotFoundError:
        df = pd.DataFrame()

    # Append the form data to the DataFrame
    df = df.append(data, ignore_index=True)

    # Write the updated DataFrame to the Excel file
    df.to_excel('form_data.xlsx', index=False)

    return 'Form data submitted successfully!'

if __name__ == '__main__':
    app.run()
