# -*- coding: utf-8 -*-
from flask import (
    Blueprint, render_template, session, g, flash, request, redirect, url_for,
    current_app
)
from app.common.utils import get_signer, Logger, Utilities, ApiCalls, Response
import json
import requests


auth_bp = Blueprint('auth_bp', __name__)


@auth_bp.before_app_request
def load_user():
    g.user = None
    if 'user_data' in session:
        try:
            g.user = session['user_data']
        except:
            pass


@auth_bp.route('/', methods=['GET'])
@auth_bp.route('/login', methods=['GET'])
def login_page():
    return render_template('auth/login.html')


@auth_bp.route('/login', methods=['POST'])
def login():
    request_id = Utilities.generate_session_id()
    logger = Logger(request_id).event("LOGIN")

    try:
        params = json.loads(request.data.decode('utf-8'))
        response = ApiCalls().request_api(req_params=params, route='/login')
        logger.event("Login response: {}".format(response))

        if response.get('code') == '00':
            logger.event("Login successful")
            session['user_data'] = response.get('data')
        
        return response

    except Exception as ex:
        raise ex
        return Response.input_error(description="An error occurred: {}".format(str(ex)))

@auth_bp.route('/logout', methods=['GET'])
def logout():
    request_id = Utilities.generate_session_id()
    logger = Logger(request_id).event("LOGOUT")

    try:
        session.pop('user_data', None)
        return redirect(url_for('auth_bp.login_page'))

    except Exception as ex:
        raise ex
        return Response.input_error(description="An error occurred: {}".format(str(ex)))


