import logging
import time
from aiogram import Bot, Dispatcher, executor, types
import Parser
def Bot():
    bot = Bot(token="Ваш токен:") # bot object
    dp = Dispatcher(bot) # dispatcher