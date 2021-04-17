# -*- coding: utf-8 -*-
from app.application import db
from datetime import datetime
from app.common.utils import SlickEnum


class BaseDocument(db.Document):

    created_at = db.DateTimeField(
        verbose_name=u'Criado em',
        required=True
    )
    updated_at = db.DateTimeField(
        verbose_name=u'Atualizado em',
        required=True
    )

    meta = {'abstract': True}

    def save(self, *args, **kwargs):
        if not self.created_at:
            self.created_at = datetime.now()
        self.updated_at = datetime.now()
        return super(BaseDocument, self).save(*args, **kwargs)



class Admin(db.Document):
    class Status(SlickEnum):
        ACTIVE = "ACTIVE"
        INACTIVE = "INACTIVE"

    name = db.StringField(required=True)
    username = db.StringField(required=True)
    email = db.StringField(required=True)
    password = db.StringField(null=True)
    status = db.StringField(required=True, default="ACTIVE", choices=Status.to_list())
    password_changed = db.BooleanField(default=False)
    last_password_change_date = db.DateTimeField(null=True, default=None)
    created_at = db.DateTimeField(default=datetime.utcnow)
    modified_at = db.DateTimeField(null=True, default=None)

    meta = {'indexes': [
        {'fields': ['$name', "$email"],
         'weights': {'name': 1, 'email': 1}
         }
    ]}

    def __repr__(self):
        return '< Admin %r >' % self.email

    def to_dict(self):
        dict_obj = {}
        for column, value in self._fields.items():
            if column == "created_at":
                dict_obj[column] = str(getattr(self, column))
            elif column == "last_password_change_date" and getattr(self, column) is not None:
                dict_obj[column] = str(getattr(self, column))
            elif column == "modified_at" and getattr(self, column) is not None:
                dict_obj[column] = str(getattr(self, column))
            elif column == "password":
                pass
            else:
                dict_obj[column] = getattr(self, column)

        if "id" in dict_obj:
            dict_obj["id"] = str(dict_obj["id"])

        return dict_obj


class Measurement(db.Document):
    class Type(SlickEnum):
        TEMPERATURE = "TEMPERATURE"
        TVOC = "TVOC"
        LIGHT_INTENSITY = "LIGHT_INTENSITY"
        HUMIDITY = "HUMIDITY"
        ECO2 = "ECO2"
        ETHANOL = "ETHANOL"
        H2 = "H2"

    type = db.StringField(reqired=True, choices=Type.to_list())
    value = db.DecimalField()
    created_at = db.DateTimeField(default=datetime.utcnow)

    def __repr__(self):
        return '< Measurement %r >' % self.type

    def to_dict(self):
        dict_obj = {}
        for column, value in self._fields.items():
            if column == "created_at" or column == "value":
                dict_obj[column] = str(getattr(self, column))
            else:
                dict_obj[column] = getattr(self, column)

        if "id" in dict_obj:
            dict_obj["id"] = str(dict_obj["id"])
        return dict_obj

    def to_dict_dashboard(self):
        dict_obj = {}
        for column, value in self._fields.items():
            if column == "created_at":
                dict_obj[column] = datetime.strftime(getattr(self, column), "%H:%M")
            elif column == "value":
                dict_obj[column] = str(getattr(self, column))
            else:
                dict_obj[column] = getattr(self, column)

        if "id" in dict_obj:
            dict_obj["id"] = str(dict_obj["id"])
        return dict_obj






