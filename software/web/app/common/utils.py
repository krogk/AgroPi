import uuid
import requests
import datetime
from enum import Enum

# -*- coding: utf-8 -*-
from flask import current_app, g, jsonify
from itsdangerous import URLSafeTimedSerializer
from app.config import API_URL, API_HEADERS, CPP_SERVER_URL


def get_signer():
    secret = current_app.config['SECRET_KEY']
    s = URLSafeTimedSerializer(secret)
    return s


class Utilities:
    
    @staticmethod
    def generate_session_id(length=32):
        if length <= 8:
            length = 8 
        return str(uuid.uuid4()).replace('-', '')[:length]

    @staticmethod
    def format_date_string(date_string):
        return (datetime.datetime.strptime(date_string, "%Y-%m-%d %H:%M:%S.%f")).strftime("%d %B, %Y %H:%M:%S")

    @staticmethod
    def get_dates_in_range(start_date, end_date):
        start_date_obj = datetime.datetime.strptime(start_date, "%d/%m/%Y %H:%M")
        end_date_obj = datetime.datetime.strptime(end_date, "%d/%m/%Y %H:%M")

        dates = [datetime.datetime.strftime(start_date_obj, "%H:00")]
        date_ = start_date_obj + datetime.timedelta(hours=1)
        while date_ <= end_date_obj:
            dates.append(datetime.datetime.strftime(date_, "%H:00"))
            date_ = date_ + datetime.timedelta(hours=1)

        return dates


class SlickEnum(Enum):

    @classmethod
    def has_value(cls, value):
        """
        Method to check whether any of the SlickEnum's object has the given value
        :param value:
        :return:
        """
        return any(value == enum.value for enum in cls)

    @classmethod
    def to_list(cls):
        """
        Method to return a list of the SlickEnum class's value set.
        :return:
        """
        return [enum.value for enum in cls]

##########################################################################################
##########################################  LOGGER
##########################################################################################
class Logger:
    class Type(SlickEnum): #SlickEnum
        EVENT = "EVENT"
        INFO = "INFO"
        DEBUG = "DEBUG"
        WARN = "WARN"
        ERROR = "ERROR"

    def __init__(self, request_id="***"):
        self.request_id = request_id

    def __get_format__(self, type, str_to_log):
        return "{} | {} | {} | {}".format(self.__get_current_date__(), self.request_id, type, str_to_log)

    def __get_current_date__(self):
        return datetime.datetime.now().strftime("%d/%m/%Y @ %H:%M:%S")

    def console(self, type, str_to_log):
        print("{} | {} | {} | {}".format(self.__get_current_date__(), self.request_id, type.name, str_to_log))

    def event(self, str_to_log):
        print("---------------------------------------------------------------------------------------------")
        print(self.__get_format__(self.Type.EVENT.name, str_to_log))
        print("---------------------------------------------------------------------------------------------")
        return self

    def info(self, str_to_log):
        print(self.__get_format__(self.Type.INFO.name, str_to_log))
        return self

    def debug(self, str_to_log):
        print(self.__get_format__(self.Type.DEBUG.name, str_to_log))
        return self

    def warn(self, str_to_log):
        print(self.__get_format__(self.Type.WARN.name, str_to_log))
        return self

    def error(self, str_to_log):
        print(self.__get_format__(self.Type.ERROR.name, str_to_log))
        return self

class ApiCalls:
    """
    This class contains all function calls to external APIs
    """

    @staticmethod
    def request_api(req_params, route='', method='post', url=CPP_SERVER_URL, headers=API_HEADERS):
        """
        This function makes and get response form fusion Virtuals account API

        @Params : req_params [dict]
        @Params : models [str]
        @Params : functions [str]
        @Params : method [str] val ['post', 'get']
        @Params : url [str]
        @Params : headers [dict]
        """
        req_data = {}
        if route != '':
            url += route

        if route != {}:
            req_data = req_params


        print("USER SESSION::: {}".format(g.user))
        if g.user:
            headers['Session-Token'] = g.user.get('session_token')

        print(req_data)
        print(url)
        print(headers)

        if method == 'post':
            r = requests.post(url, json=req_data, headers=headers, verify=False).json()
        elif method == 'get':
            r = requests.get(url, params=req_data, headers=headers, verify=False).json()
        elif method == 'put':
            r = requests.put(url, json=req_data, headers=headers, verify=False).json()
        elif method == 'delete':
            r = requests.delete(url, json=req_data, headers=headers, verify=False).json()
        elif method == 'patch':
            r = requests.patch(url, json=req_data, headers=headers, verify=False).json()
        else:
            return {"code": "00", "msg": "Method is not supported."}
        return r

class ResponseCode(SlickEnum):
    SUCCESS = "00"
    INTERNAL_SYSTEM_ERROR = "01"
    EXTERNAL_SYSTEM_ERROR = "02"
    # SYSTEM_ERROR = "01"
    INPUT_ERROR = "03"
    AUTH_ERROR = "04"


class Response:
    @staticmethod
    def ok_response(msg='Success', data={}, nav=None):
        response = {"code": "00", 'data': data, 'msg': msg, 'error': None}
        if nav:
            response.update({'nav': nav})
        return jsonify(response), 200

    @staticmethod
    def general_error(description='Error', code=ResponseCode.INPUT_ERROR.value, type=None):
        return jsonify({'code': "01", 'msg': description, 'data': None})

    @staticmethod
    def system_error(description='Error', code=None, type=None):
        return jsonify({'code': "02", 'msg': description, 'data': None})

    @staticmethod
    def input_error(description="Input Error", code=None, type=None):
        return jsonify({'code': "03", 'msg': description, 'data': None})

    @staticmethod
    def auth_error(description="Auth Error", code=None, type=None):
        return jsonify({'code': "04", 'msg': "You are not allowed to access this resource", 'data': None})

    @staticmethod
    def session_expired(description="Session expired", code=None, type=None):
        return jsonify({'code': "05", 'msg': description, 'data': None})
