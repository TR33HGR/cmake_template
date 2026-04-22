import requests
import json

# Define the URL of the localhost server
url = "http://localhost:5000/"  # Adjust port and endpoint as needed

# Define the JSON payload to send
payload = {
    "user": "Bob",
    "message": "Hello from client!",
}

# Set headers to indicate JSON content
headers = {
    "Content-Type": "application/json"
}

try:
    # Send POST request with JSON payload
    response = requests.post(url, data=json.dumps(payload), headers=headers)

    # Check response status
    if response.status_code == 200:
        print("JSON message sent successfully")
        print("Response:", response.json())
    else:
        print(f"Failed to send message. Status code: {response.status_code}")
        print("Response:", response.text)

except requests.exceptions.ConnectionError:
    print("Failed to connect to the server. Make sure the server is running on localhost.")
except Exception as e:
    print(f"An error occurred: {str(e)}")
