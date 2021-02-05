var time_series_chart = null;

function get_dashboard_data(){
    var start_date = $('.date-range').data('daterangepicker').startDate._d;
    var end_date = $('.date-range').data('daterangepicker').endDate._d;

    var today = moment();

    if (start_date != ""){
        start_date = $.date(start_date);
    }
    else{
        start_date = $.date(today.subtract(29, 'days'));
    }

    if (end_date != ""){
        end_date = $.date(end_date);
    }
    else{
        end_date = $.date(today);
    }

    form_data = {
        'start_date': start_date,
        'end_date': end_date
    }
    form_data = JSON.stringify(form_data);
    $.postJSON("/dashboard", form_data, function(data){
        console.log(data);
        if (data.code == "00") {
            count_data = data.data;

            $('#category-count').html(count_data.category_count);
            $('#firm-count').html(count_data.firm_count);
            $('#user-count').html(count_data.user_count);
            $('#legal-aid-count').html(count_data.legal_aid_count);
            $('#firm-requests-count').html(count_data.firm_requests_count);

            display_time_series_chart(count_data.legal_aid_chart, count_data.firm_requests_chart);
        }
        else{
            notify_failure("Error", data.msg);
        }
    });
}

function display_time_series_chart(legal_aid_chart_data, firm_requests_chart_data){
    if (time_series_chart == null){
        var options={
        chart:{
            height:320,
            type:"area",
            stacked:!0,
            toolbar:{
                show:!1,
                autoSelected:"zoom"}
            },
            colors:["#2a77f4","#a5c2f1"],
            dataLabels:{enabled:!1},
            stroke:{
                curve:"smooth",
                width:[1.5,1.5],
                dashArray:[0,4],
                lineCap:"round"
            },
            grid:{
                padding:{
                    left:0,
                    right:0
                },
                strokeDashArray:3
            },
            markers:{
                size:0,
                hover:{size:0}
            },
            series:[{
                name:"Legal Aid Requests",
                data:legal_aid_chart_data.values
            },
            {
                name:"Firm Requests",
                data:firm_requests_chart_data.values
            }],
            xaxis:{
                type:"day",
                categories:legal_aid_chart_data.labels,
            axisBorder:{
                show:!0
            },
            axisTicks:{
                show:!0}
            },
            fill:{
                type:"gradient",
                gradient:{
                    shadeIntensity:1,
                    opacityFrom:.4,
                    opacityTo:.3,
                    stops:[0,90,100]
                }
            },
            tooltip:{
                x:{
                    format:"dd/MM/yy HH:mm"
                }
            },
            legend:{
                position:"top",
                horizontalAlign:"right"
            }
        };
        time_series_chart = new ApexCharts(document.querySelector("#time-series-chart"), options);
        time_series_chart.render();
    }
    else{
        time_series_chart.updateSeries([{
            name:"Legal Aid Requests",
            data:legal_aid_chart_data.values
        },
        {
            name:"Firm Requests",
            data:firm_requests_chart_data.values
        }]);

        time_series_chart.updateOptions({
            xaxis:{
                type:"day",
                categories:legal_aid_chart_data.labels
            }
        });
    }
    
}












