"""
API Wrapper for interacting with TV provider's API
"""

# Imports
from fastapi import FastAPI
from decouple import config
import logging
import os

# Spotipy Imports
from spotipy.oauth2 import SpotifyOAuth
from spotipy import Spotify


# Define environment variables
os.environ["SPOTIPY_CLIENT_ID"] = config("SPOTIPY_CLIENT_ID")  #type: ignore
os.environ["SPOTIPY_CLIENT_SECRET"] = config("SPOTIPY_CLIENT_SECRET")  #type: ignore
os.environ["SPOTIPY_REDIRECT_URI"] = config("SPOTIPY_REDIRECT_URI")  #type: ignore

# Authentication
sp = Spotify(auth_manager=SpotifyOAuth(scope=config("SPOTIPY_SCOPE")))

# Logging
logging.basicConfig(
    level=logging.INFO,
    format='%(levelname)s:     %(message)s',
    filemode='w'
)
logger = logging.getLogger(__name__)


class Service(FastAPI):
    """Base class for service providers"""

    def __init__(self, *args, **kwargs) -> None:
        super().__init__(debug=True, version="0.0.1", *args, **kwargs)
        self.service = self.__class__.__name__


class Spotify(Service):
    """Spotify Service"""

    def __init__(self, *args, **kwargs) -> None:
        super().__init__(
            title="Spotify API",
            description="API for interacting with Spotify's API",
            *args, **kwargs
        )

        # Endpoints
        @self.get("/")
        async def root():
            """Home page"""
            return {'service': self.service}
        
        @self.get("/on-off")
        def onoff():
            """ON/OFF Endpoint: Toggle play/pause"""
            PLAYBACK = sp.current_playback()['is_playing']  #type: ignore
            if PLAYBACK:
                sp.pause_playback()
                logging.info("Playback Paused")
                return "Playback Paused"
            else:
                sp.start_playback()
                logging.info("Playback Resumed")
                return "Playback Resumed"
        
        @self.get("/channel-up")
        def chup():
            """CHANNEL UP Endpoint: Next Song"""
            sp.next_track()
            logging.info("Playing Next Song")
            return "Playing Next Song"
        
        @self.get("/channel-down")
        def chdown():
            """CHANNEL DOWN Endpoint: Previous Song"""
            sp.previous_track()
            logging.info("Playing Previous Song")
            return "Playing Previous Song"


class Netflix(Service):
    """Netflix Service"""

    def __init__(self, *args, **kwargs) -> None:
        super().__init__(
            title="Netflix API",
            description="API for interacting with Netflix's API",
            *args, **kwargs
        )

        # Endpoints
        @self.get("/")
        async def root():
            """Home page"""
            return {'service': self.service}
        
        @self.get("/on-off")
        def onoff():
            """Turn on/off service"""
            return "Netflix Play/Pause"
        
        @self.get("/channel-up")
        def chup():
            """Change channel up"""
            return "Next Episode"
        
        @self.get("/channel-down")
        def chdown():
            """Change channel down"""
            return "Previous Episode"


spotify = Spotify()
netflix = Netflix()
