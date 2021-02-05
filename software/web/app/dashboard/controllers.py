import math
from app.common.utils import Logger, ApiCalls, Response, Utilities

class DashboardControllers:
    """
    Dashboard controller
    """
    
    def __init__(self, session_id):
        self.session_id = session_id
        self.logger = Logger(self.session_id).event("DASHBORD_CONTROLLER")

    def get_dashboard_data(self, request_data):
        try:
            return ApiCalls().request_api(req_params=request_data, method='post', route='/dashboard')
        except Exception as ex:
            return Response.input_error(description="An error occurred: {}".format(str(ex)))

