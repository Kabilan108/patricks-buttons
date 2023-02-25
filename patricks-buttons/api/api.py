"""
API Wrapper for interacting with TV provider's API
"""

# Imports
from fastapi import FastAPI

# Create FastAPI instance
app = FastAPI()


@app.get("/")
def read_root():
    return "Home"

@app.get("/on-off")
def onoff():
    return "On/Off"

@app.get("/channel-up")
def chup():
    return "Channel Up"

@app.get("/channel-down")
def chdown():
    return "Channel Down"


# if __name__ == "__main__":
#     import uvicorn
#     uvicorn.run(app, host="192.168.6.216", port=80, reload=True)