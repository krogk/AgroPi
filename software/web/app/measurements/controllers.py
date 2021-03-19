import math
from app.common.utils import Logger, ApiCalls, Response, Utilities
from app.common.models import Measurement
import app.application as application

class MeasurementsControllers:
    """
    Measurements controller
    """
    
    def __init__(self, session_id):
        self.session_id = session_id
        self.logger = Logger(self.session_id).event("MEASUREMENTS_CONTROLLER")

    def add_measurement(self, request_data):
        try:
            if request_data.get('type') not in Measurement.Type.to_list():
                return Response.input_error(description="Type must be one of {}".format(Measurement.Type.to_list()))

            measurement = Measurement(type=request_data.get('type'), value=request_data.get('value')).save()
            application.socketio.emit('measurement_updated', measurement.to_dict_dashboard())

            return Response.ok_response()
        except Exception as ex:
            return Response.input_error(description="An error occurred: {}".format(str(ex)))

