# -*- coding: utf-8 -*-

# flask core settings
DEBUG = True
TESTING = False
SECRET_KEY = 'qh\x98\xc4o\xc4]\x8f\x8d\x93\xa4\xec\xc5\xfd]\xf8\xb1c\x84\x86\xa7A\xcb\xc0'
PERMANENT_SESSION_LIFETIME = 60 * 60 * 24 * 30

# flask wtf settings
WTF_CSRF_ENABLED = True

# flask mail settings
MAIL_DEFAULT_SENDER = 'noreply@yourmail.com'

# project settings
PROJECT_PASSWORD_HASH_METHOD = 'pbkdf2:sha1'
PROJECT_SITE_NAME = u'AgroPi'
PROJECT_SITE_URL = u'http://127.0.0.1:5000'
PROJECT_SIGNUP_TOKEN_MAX_AGE = 60 * 60 * 24 * 7  # in seconds
PROJECT_RECOVER_PASSWORD_TOKEN_MAX_AGE = 60 * 60 * 24 * 7  # in seconds

#db settings
MONGODB_DB = "agropi_db"

API_URL = ''
CPP_SERVER_URL = 'http://127.0.0.1:80'
API_HEADERS = {}
OPERATION_CODES = {
	'MAX_LIGHT': 1,
	'MIN_LIGHT': 2,
	'MAX_TEMP': 3,
	'MIN_TEMP': 4,
	'MAX_TVOC': 5,
	'MIN_TVOC': 6,
	'MAX_ECO2': 7,
	'MIN_ECO2': 8,
	'MAX_ETHANOL': 9,
	'MIN_ETHANOL': 10,
	'MAX_H2': 11,
	'MIN_H2': 12,
	'MAX_HUMIDITY': 13,
	'MIN_HUMIDITY': 14,
	'HEATING_TOGGLE': 128,
	'AIRFLOW_TOGGLE': 129,
	'LIGHT_TOGGLE': 130,
}
