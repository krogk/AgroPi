import math
from datetime import datetime
from mongoengine.queryset.visitor import Q
from app.common.utils import Logger, ApiCalls, Response, Utilities
from app.common.models import Measurement

class DashboardControllers:
    """
    Dashboard controller
    """
    
    def __init__(self, session_id):
        self.session_id = session_id
        self.logger = Logger(self.session_id).event("DASHBORD_CONTROLLER")

    def get_dashboard_data(self, params):
        try:
            if 'start_date' not in params and 'end_date' not in params:
                return Response.input_error(description="start_date and end_date required")
            
            dashboard_data = dict()
            date_format = "%d/%m/%Y %H:%M:%S"
            # dates_in_range = Utilities.get_dates_in_range(params['start_date'],  params['end_date'])

            for measurement_type in Measurement.Type.to_list():
                measurement_data = Measurement.objects(
                    Q(created_at__gte=datetime.strptime(params['start_date'] + ":00", date_format)) & 
                    Q(created_at__lte=datetime.strptime(params['end_date'] + ":59", date_format)) &
                    Q(type=measurement_type))
                
                data_values = []
                time_values = []
                for data in measurement_data:
                    data_values.append(float(data.value))
                    time_values.append(datetime.strftime(data.created_at, "%H:%M"))

                dashboard_data[measurement_type.lower()] = {'labels': time_values, 'values': data_values}
            
            return Response.ok_response(data=dashboard_data)
        except Exception as ex:
            return Response.input_error(description="An error occurred: {}".format(str(ex)))

