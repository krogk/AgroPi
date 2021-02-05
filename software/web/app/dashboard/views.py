# -*- coding: utf-8 -*-
import json
from flask import (
    Blueprint, render_template, session, g, flash, request, redirect, url_for,
    current_app
)
from app.common.utils import Logger, Utilities, ApiCalls, Response
from app.common.decorators import login_required
from app.dashboard.controllers import DashboardControllers


dashboard_bp = Blueprint('dashboard_bp', __name__)


@dashboard_bp.before_app_request
def load_user():
    g.user = None
    if 'user_data' in session:
        try:
            g.user = session['user_data']
        except:
            pass


@dashboard_bp.route('/dashboard', methods=['GET', 'POST'])
# @login_required
def dashboard_page():
    if request.method == 'GET':
    	return render_template('dashboard/dashboard.html')

    else:
    	request_id = Utilities.generate_session_id()
    	params = json.loads(request.data.decode('utf-8'))
    	return DashboardControllers(request_id).get_dashboard_data(params)
