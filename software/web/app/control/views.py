# -*- coding: utf-8 -*-
import json
from flask import (
    Blueprint, render_template, session, g, flash, request, redirect, url_for,
    current_app
)
from app.common.utils import Logger, Utilities, ApiCalls, Response
from app.common.decorators import login_required
from app.control.controllers import ControlControllers


control_bp = Blueprint('control_bp', __name__)


@control_bp.before_app_request
def load_user():
    g.user = None
    if 'user_data' in session:
        try:
            g.user = session['user_data']
        except:
            pass


@control_bp.route('/control', methods=['GET', 'POST'])
# @login_required
def control_page():
    return render_template('control/control.html')

@control_bp.route('/control', methods=['PUT'])
# @login_required
def update_values():
    request_id = Utilities.generate_session_id()
    params = json.loads(request.data.decode('utf-8'))
    return ControlControllers(request_id).update_sensor_values(params)