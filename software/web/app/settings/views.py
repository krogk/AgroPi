# -*- coding: utf-8 -*-
import json
from flask import (
    Blueprint, render_template, session, g, flash, request, redirect, url_for,
    current_app
)
from app.common.utils import Logger, Utilities, ApiCalls, Response
from app.common.decorators import login_required
from app.settings.controllers import SettingsControllers


settings_bp = Blueprint('settings_bp', __name__)


@settings_bp.before_app_request
def load_user():
    g.user = None
    if 'user_data' in session:
        try:
            g.user = session['user_data']
        except:
            pass


@settings_bp.route('/settings', methods=['GET', 'POST'])
# @login_required
def settings_page():
    return render_template('settings/settings.html')
