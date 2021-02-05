
function login(element, callback){
    var email = $('#txt-email').val();
    var password = $('#txt-password').val();

    valid_email = validate_text_feild(email, "#txt-email", 'email');
    valid_password = validate_text_feild(password, "#txt-password");

    if( valid_email && valid_password ){
        $('#login-loader').css('display', '');
        $('#btn-login').attr('disabled', true);

        form_data = JSON.stringify({
          "email": email,
          "password": password
        });
        console.log(form_data);
        
        $.postJSON("/login", form_data, function(data){
            $('#btn-login').css('disabled', false);
            $('#login-loader').attr('display', 'none');
            
            console.log(data);
            if (data.code == "00") {
                window.location = "/dashboard";

            }
            else if(data.code == "01"){
              show_error_alert(data.msg);
            }
            else{
                show_error_alert(data.msg);
            }
        });
    }
    else if(!valid_email){
        show_error_alert("Enter a valid email");
    }
    else if(!valid_password){
        show_error_alert("Enter password");
    }
}



function show_error_alert(msg){
    $('#alert-div').css('display', '');
    $('#alert-msg').html(msg);

    setTimeout(() => {
        $('#alert-div').css('display', 'none');
    }, 2000);
}


