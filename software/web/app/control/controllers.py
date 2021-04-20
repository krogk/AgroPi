import math
import requests
from app.common.utils import Logger, ApiCalls, Response, Utilities
from app.config import OPERATION_CODES, CPP_SERVER_URL

class ControlControllers:
    """
    Control controller
    """
    
    def __init__(self, session_id):
        self.session_id = session_id
        self.logger = Logger(self.session_id).event("CONTROL_CONTROLLER")

    def get_control_data(self, request_data):
        try:
            return ApiCalls().request_api(req_params=request_data, method='post', route='/control')
        except Exception as ex:
            return Response.input_error(description="An error occurred: {}".format(str(ex)))

    def update_sensor_values(self, request_data):
        # return Response.ok_response()
        try:
            for key, value in request_data.items():
                params = {
                    'operation': OPERATION_CODES.get(key.upper()),
                    'value': value
                }
                self.logger.event("Request to cpp: {}".format(params))
                # ApiCalls().request_api(req_params=params, method='post', route='/sensor/')
                response = requests.post(url="{}/sensor/".format(CPP_SERVER_URL), data=params, verify=False).text
                # response = {}
                self.logger.event("Response from cpp: {}".format(response))
            return Response.ok_response()
        except Exception as ex:
            return Response.input_error(description="An error occurred: {}".format(str(ex)))

