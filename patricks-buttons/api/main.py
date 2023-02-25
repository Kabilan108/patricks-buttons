"""
Main script for Patrick's Buttons API
"""

from decouple import config
import uvicorn


if __name__ == "__main__":
    HOST, PORT = config("HOST"), int(config("PORT"))
    uvicorn.run("api:app", host=HOST, port=PORT, reload=True)
