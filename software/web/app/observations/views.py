# -*- coding: utf-8 -*-
import json
from flask import (
    Blueprint, render_template, session, g, flash, request, redirect, url_for,
    current_app
)
from app.common.utils import Logger, Utilities, ApiCalls, Response
from app.common.decorators import login_required
from app.observations.controllers import ObservationsControllers


observations_bp = Blueprint('observations_bp', __name__)


@observations_bp.before_app_request
def load_user():
    g.user = None
    if 'user_data' in session:
        try:
            g.user = session['user_data']
        except:
            pass


@observations_bp.route('/observations', methods=['GET'])
# @login_required
def observations_page():
    return render_template('observations/observations.html')
