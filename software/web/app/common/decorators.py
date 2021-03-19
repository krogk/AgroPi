# -*- coding: utf-8 -*-
from functools import wraps
import traceback
from flask import request, jsonify, g, request, redirect, url_for
from app.common.utils import Logger


def get_page(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        page = request.args.get('page', 1)
        try:
            kwargs['page'] = int(page)
        except:
            kwargs['page'] = 1
        return f(*args, **kwargs)
    return decorated_function


def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if g.user is None:
            return redirect(url_for('auth_bp.login_page'))
        return f(*args, **kwargs)
    return decorated_function

def required_params(*required_parameters):
    """
    Utility function for checking request body parameters flagged as required
    """

    def wrapper(f):
        @wraps(f)
        def wrapped(*args, **kwargs):
            logger = Logger("request_id").event("AUTHENTICATE_USER")
            try:
                # extract the json body into a python dict
                request_data = request.form.to_dict() or json.loads(request.data.decode('utf-8'))
            except Exception as e:
                traceback.print_exc()
                response = {"code": "01", "msg": "Malformed request body", "data": {}}
                return jsonify(**response), 200

            logger.event("Request parameters received: {}".format(request_data))
            logger.event("Request parameters required: {}".format(required_parameters))

            # check the parameters received against the paramters specified by the endpoint and store any missing parameters
            missing_params = []
            for param in required_parameters:
                if param not in request_data:
                    missing_params.append(param)

            # display the missing parameters
            if len(missing_params) > 0:
                response = {"code": "01",
                            "msg": "The following required parameters are missing: {}".format(missing_params),
                            "data": {}}
                return jsonify(**response), 200
            return f(*args, **kwargs)

        return wrapped
    return wrapper
