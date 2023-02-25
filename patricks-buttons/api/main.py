"""
Main script for Patrick's Buttons API
"""

from InquirerPy.base.control import Choice
from InquirerPy import prompt
from decouple import config
import uvicorn


def select_service():
    """Select service to interact with"""

    questions = [
        {
            "type": "list",
            "message": "Select service to control",
            "name": "service",
            "choices": [
                "Spotify",
                "YouTube",
                "Netflix",
                Choice(name="Quit", value="quit")
            ]
        }
    ]
    answers = prompt(questions)
    return answers["service"]


if __name__ == "__main__":
    HOST, PORT = config("HOST"), int(config("PORT"))
    service = select_service()
    if service == "quit":
        print("Goodbye!")
    else:
        app = f"api:{service.lower()}"
        uvicorn.run(app, host=HOST, port=PORT, reload=True)
