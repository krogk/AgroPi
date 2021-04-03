/**********************************************
            HELPER FUNCTIONS
***********************************************/

$.postFORM = function(url, data, callback) {
  return jQuery.ajax({
      type: "POST",
      url: url,
      data: data,
      dataType: 'json',
      success: callback,
      error: onAjaxError,
      timeout: 50000,
      cache: false
  });
};

$.postJSON = function(url, data, callback) {
  return jQuery.ajax({
      type: "POST",
      url: url,
      contentType: 'application/json',
      data: data,
      dataType: 'json',
      success: callback,
      error: onAjaxError,
      timeout: 50000,
      cache: false
  });
};

$.putJSON = function(url, data, callback) {
  return jQuery.ajax({
      type: "PUT",
      url: url,
      contentType: 'application/json',
      data: data,
      dataType: 'json',
      success: callback,
      error: onAjaxError,
      timeout: 50000,
      cache: false
  });
};

$.getJSON = function(url, data, callback) {
  return jQuery.ajax({
      type: "GET",
      url: url,
      contentType: 'application/json',
      dataType: 'json',
      success: callback,
      error: onAjaxError,
      timeout: 50000,
      cache: false
  });
};

function onAjaxError(xhr, status, error){
//    hide_loader();
    notify_failure("Request Error", "Request failed. Kindly try again.", "error");
}


function validate_text_feild(value, element, inputType){

  var regemail = /^([\w-\.]+)@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.)|(([\w-]+\.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\]?)$/;
  var regname = /^[a-zA-Z]+([\s\-]?[a-zA-Z])*$/;
  var regphone = /\d{12}$/;
  var regph = /^0+\d{9}$/;
  var regnumeric = /^([0-9])+$/;
  var regdecimal = /^[1-9]\d*(\.\d+)?$/;
  var regalphanumeric = /^([0-9]|[a-zA-Z])+([0-9a-zA-Z]+)$/

  if (inputType == 'name'){
    res = regname.test(value);
  }
  else if (inputType == 'phone'){
    res = regphone.test(value) || regph.test(value);
  }
  else if (inputType == 'email'){
    res = regemail.test(value);
  }
  else if (inputType == 'alphanumeric'){
    res = regalphanumeric.test(value);
  }
  else if (inputType == 'number'){
    res = regnumeric.test(value);
  }
  else if (inputType == 'decimal'){
    res = regdecimal.test(value);
  }
  else{
    res = true;
  }

  if((value == "" || value == undefined) || res == false){
    //if(!$(element).hasClass("has-error")){
        // $(element).removeClass("has-success");
        // $(element).toggleClass("has-error");
      //}
      if (inputType == 'empty'){
        return true;
      }

      $(element).removeAttr("border-bottom");
      $(element).removeAttr("box-shadow");
      // $(element).css("border-bottom", "1px solid #FF0000");
      // $(element).css("box-shadow", "0 1px 0 0 #FF0000");
      return false;
    }else{
      //if(!$(element).parent().hasClass("has-success")){
        // $(element).parent().removeClass("has-error");
        // $(element).parent().toggleClass("has-success");
      //}
      $(element).removeAttr("border-bottom");
      $(element).removeAttr("box-shadow");
      // $(element).css("border-bottom", "1px solid #00E700");
      // $(element).css("box-shadow", "0 1px 0 0 #00E700");
      return true;
    }
};


function LoadTable(element, data_source_url) {
  $(element).dataTable({
    "scrollY": "54vh",
    // "scrollX": true,
    "scrollCollapse": true,
    "processing": true,
    "serverSide": true,
    "bSort": false,
    "order": [],
    "ajax": {
      url: data_source_url,
      type: "POST",
      data: {}
    }
  });
}


function notify_success(message){
  toastr.success(message);
}

function notify_failure(message){
  toastr.error(message);
}


function show_button_loader(element){
  $(element + ' span').css('margin-right', '10px');
  $(element + ' span').css('display', '');
  $(element).attr('disabled', true);
}

function clear_button_loader(element){
  $(element + ' span').css('display', 'none');
  $(element).attr('disabled', false);
}


function show_error_alert(msg){
    $('#alert-div').css('display', '');
    $('#alert-msg').html(msg);

    setTimeout(() => {
        $('#alert-div').css('display', 'none');
    }, 2000);
}


function show_invalid_input(element, msg){
  $(element).addClass("is-invalid");
  $(element + "-invalid").html(msg);
  $(element + "-invalid").css('display', '');

  $(element).on('change', function(e){
    $(element).removeClass("is-invalid");
    $(element + "-invalid").html("");
    $(element + "-invalid").css('display', 'none');
  })
}

function date_format(date_string){
  return moment(date_string).format("Do MMM YYYY, hh:mmA");
}

$.date = function(dateObject) {
  var d = new Date(dateObject);
  var day = d.getDate();
  var month = d.getMonth() + 1;
  var year = d.getFullYear();
  var hour = d.getHours();
  var minute = String(d.getMinutes());


  if (day < 10) {
      day = "0" + day;
  }
  if (month < 10) {
      month = "0" + month;
  }

  if (String(hour).length == 1){
    hour = "0" + hour;
  }
  if(String(minute).length == 1){
    minute = "0" + minute;
  }

  var date = day + "/" + month + "/" + year + " " + hour + ":" + minute;

  return date;
};

