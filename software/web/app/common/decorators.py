# -*- coding: utf-8 -*-
from functools import wraps
from flask import request
from flask import g, request, redirect, url_for


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