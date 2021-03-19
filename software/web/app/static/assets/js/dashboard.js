$(document).ready(function(){
    init_chart_configs();
    // sending a connect request to the server.
    var socket = io.connect('http://localhost:5050');

    socket.on('after_connect', function(msg){
       console.log('After connect', msg);
    });


    socket.on('measurement_updated', function(data) {
        console.log('Measurement updated', data);
        if (data.type == "TEMPERATURE"){
            display_temperature_chart(data, true);
        }
        else if(data.type == "HUMIDITY"){
            display_humidity_chart(data, true);
        }
        else if(data.type == "WATER_LEVEL"){
            display_water_level_chart(data, true);
        }
        else if(data.type == "LIGHT_INTENSITY"){
            display_light_intensity_chart(data, true);
        }
    });
});




var time_series_chart = null;
var temperature_chart = null;
var humidity_chart = null;
var water_level_chart = null;
var light_intensity_chart = null;

function get_dashboard_data(){
    var start_date = $('.date-range').data('daterangepicker').startDate._d;
    var end_date = $('.date-range').data('daterangepicker').endDate._d;

    var now = moment();

    if (start_date != ""){
        start_date = $.date(start_date);
    }
    else{
        start_date = $.date(now.startOf('hour').subtract(5, 'hour'));
    }

    if (end_date != ""){
        end_date = $.date(end_date);
    }
    else{
        end_date = $.date(now.startOf('hour'));
    }

    form_data = {
        'start_date': start_date,
        'end_date': end_date
    }
    form_data = JSON.stringify(form_data);
    console.log(form_data);
    $.postJSON("/dashboard", form_data, function(data){
        console.log(data);
        if (data.code == "00") {
            display_temperature_chart(data.data.temperature);
            display_humidity_chart(data.data.humidity);
            display_water_level_chart(data.data.water_level);
            display_light_intensity_chart(data.data.light_intensity);
            // display_time_series_chart(count_data.legal_aid_chart, count_data.firm_requests_chart);
        }
        else{
            notify_failure("Error", data.msg);
        }
    });
}

function display_temperature_chart(data, single_update){
    
    if(temperature_chart == null){
        ctx = document.getElementById('temperature-chart').getContext("2d");

        gradientStroke = ctx.createLinearGradient(500, 0, 100, 0);
        gradientStroke.addColorStop(0, '#80b6f4');
        gradientStroke.addColorStop(1, chartColor);

        gradientFill = ctx.createLinearGradient(0, 170, 0, 50);
        gradientFill.addColorStop(0, "rgba(128, 182, 244, 0)");
        gradientFill.addColorStop(1, "rgba(249, 99, 59, 0.40)");

        temperature_chart = new Chart(ctx, {
          type: 'line',
          responsive: true,
          data: {
            labels: data.labels,
            datasets: [{
              label: "Temperature",
              borderColor: "#f96332",
              pointBorderColor: "#FFF",
              pointBackgroundColor: "#f96332",
              pointBorderWidth: 2,
              pointHoverRadius: 4,
              pointHoverBorderWidth: 1,
              pointRadius: 4,
              fill: true,
              backgroundColor: gradientFill,
              borderWidth: 2,
              data: data.values
            }]
          },
          options: gradientChartOptionsConfiguration
        });
    }
    else{
        if(single_update){
            temperature_chart.data.labels.push(data.created_at);
            temperature_chart.data.datasets.forEach((dataset) => {
                dataset.data.push(parseFloat(data.value));
            });
        }
        else{
            temperature_chart.data.labels.push(data.labels);
            temperature_chart.data.datasets.forEach((dataset) => {
                dataset.data.push(parseFloat(data.values));
            });
        }
        
        temperature_chart.update();
    }
}

function display_humidity_chart(data, single_update){
    if (humidity_chart == null){
        ctx = document.getElementById('humidity-chart').getContext("2d");

        gradientStroke = ctx.createLinearGradient(500, 0, 100, 0);
        gradientStroke.addColorStop(0, '#18ce0f');
        gradientStroke.addColorStop(1, chartColor);

        gradientFill = ctx.createLinearGradient(0, 170, 0, 50);
        gradientFill.addColorStop(0, "rgba(128, 182, 244, 0)");
        gradientFill.addColorStop(1, hexToRGB('#18ce0f', 0.4));

        humidity_chart = new Chart(ctx, {
          type: 'line',
          responsive: true,
          data: {
            labels: data.labels,
            datasets: [{
              label: "Humidity",
              borderColor: "#18ce0f",
              pointBorderColor: "#FFF",
              pointBackgroundColor: "#18ce0f",
              pointBorderWidth: 2,
              pointHoverRadius: 4,
              pointHoverBorderWidth: 1,
              pointRadius: 4,
              fill: true,
              backgroundColor: gradientFill,
              borderWidth: 2,
              data: data.values
            }]
          },
          options: gradientChartOptionsConfigurationWithNumbersAndGrid
        });
    }
    else{
        if(single_update){
            humidity_chart.data.labels.push(data.created_at);
            humidity_chart.data.datasets.forEach((dataset) => {
                dataset.data.push(parseFloat(data.value));
            });
        }
        else{
            humidity_chart.data.labels.push(data.labels);
            humidity_chart.data.datasets.forEach((dataset) => {
                dataset.data.push(parseFloat(data.values));
            });
        }
        humidity_chart.update();
    }
}

function display_water_level_chart(data, single_update){
    //2CA8FF
    if (water_level_chart == null){
        ctx = document.getElementById('water-level-chart').getContext("2d");

        gradientStroke = ctx.createLinearGradient(500, 0, 100, 0);
        gradientStroke.addColorStop(0, '#2CA8FF');
        gradientStroke.addColorStop(1, chartColor);

        gradientFill = ctx.createLinearGradient(0, 170, 0, 50);
        gradientFill.addColorStop(0, "rgba(128, 182, 244, 0)");
        gradientFill.addColorStop(1, hexToRGB('#2CA8FF', 0.4));

        water_level_chart = new Chart(ctx, {
          type: 'bar',
          responsive: true,
          data: {
            labels: data.labels,
            datasets: [{
              label: "Water level",
              borderColor: "#2CA8FF",
              pointBorderColor: "#FFF",
              pointBackgroundColor: "#2CA8FF",
              pointBorderWidth: 2,
              pointHoverRadius: 4,
              pointHoverBorderWidth: 1,
              pointRadius: 4,
              fill: true,
              backgroundColor: gradientFill,
              borderWidth: 2,
              data: data.values
            }]
          },
          options: gradientChartOptionsConfigurationWithNumbersAndGrid
        });
    }
    else{
        if(single_update){
            water_level_chart.data.labels.push(data.created_at);
            water_level_chart.data.datasets.forEach((dataset) => {
                dataset.data.push(parseFloat(data.value));
            });
        }
        else{
            water_level_chart.data.labels.push(data.labels);
            water_level_chart.data.datasets.forEach((dataset) => {
                dataset.data.push(parseFloat(data.values));
            });
        }
        water_level_chart.update();
    }
}

function display_light_intensity_chart(data, single_update){
    if(light_intensity_chart == null){
        ctx = document.getElementById('light-intensity-chart').getContext("2d");

        gradientStroke = ctx.createLinearGradient(500, 0, 100, 0);
        gradientStroke.addColorStop(0, '#80b6f4');
        gradientStroke.addColorStop(1, chartColor);

        gradientFill = ctx.createLinearGradient(0, 200, 0, 50);
        gradientFill.addColorStop(0, "rgba(128, 182, 244, 0)");
        gradientFill.addColorStop(1, "rgba(255, 255, 255, 0.24)");

        light_intensity_chart = new Chart(ctx, {
          type: 'line',
          responsive: true,
          data: {
            labels: data.labels,
            datasets: [{
              label: "Temperature",
              borderColor: chartColor,
              pointBorderColor: chartColor,
              pointBackgroundColor: "#1e3d60",
              pointHoverBackgroundColor: "#1e3d60",
              pointHoverBorderColor: chartColor,
              pointBorderWidth: 2,
              pointHoverRadius: 4,
              pointHoverBorderWidth: 1,
              pointRadius: 4,
              fill: true,
              backgroundColor: gradientFill,
              borderWidth: 2,
              data: data.values
            }]
          },
          options: gradientChartOptionsBigChart
        });
    }
    else{
        if(single_update){
            light_intensity_chart.data.labels.push(data.created_at);
            light_intensity_chart.data.datasets.forEach((dataset) => {
                dataset.data.push(parseFloat(data.value));
            });
        }
        else{
            light_intensity_chart.data.labels.push(data.labels);
            light_intensity_chart.data.datasets.forEach((dataset) => {
                dataset.data.push(parseFloat(data.values));
            });
        }
        light_intensity_chart.update();
    }
}

function init_chart_configs(){
    chartColor = "#FFFFFF";

    gradientChartOptionsConfiguration = {
      maintainAspectRatio: false,
      legend: {
        display: false
      },
      tooltips: {
        bodySpacing: 4,
        mode: "nearest",
        intersect: 0,
        position: "nearest",
        xPadding: 10,
        yPadding: 10,
        caretPadding: 10
      },
      responsive: 1,
      scales: {
        yAxes: [{
          display: 0,
          gridLines: 0,
          ticks: {
            display: false
          },
          gridLines: {
            zeroLineColor: "transparent",
            drawTicks: false,
            display: false,
            drawBorder: false
          }
        }],
        xAxes: [{
          display: 0,
          gridLines: 0,
          ticks: {
            display: false
          },
          gridLines: {
            zeroLineColor: "transparent",
            drawTicks: false,
            display: false,
            drawBorder: false
          }
        }]
      },
      layout: {
        padding: {
          left: 0,
          right: 0,
          top: 15,
          bottom: 15
        }
      }
    };

    gradientChartOptionsConfigurationWithNumbersAndGrid = {
      maintainAspectRatio: false,
      legend: {
        display: false
      },
      tooltips: {
        bodySpacing: 4,
        mode: "nearest",
        intersect: 0,
        position: "nearest",
        xPadding: 10,
        yPadding: 10,
        caretPadding: 10
      },
      responsive: true,
      scales: {
        yAxes: [{
          gridLines: 0,
          gridLines: {
            zeroLineColor: "transparent",
            drawBorder: false
          }
        }],
        xAxes: [{
          display: 0,
          gridLines: 0,
          ticks: {
            display: false
          },
          gridLines: {
            zeroLineColor: "transparent",
            drawTicks: false,
            display: false,
            drawBorder: false
          }
        }]
      },
      layout: {
        padding: {
          left: 0,
          right: 0,
          top: 15,
          bottom: 15
        }
      }
    };

    gradientChartOptionsBigChart = {
        layout: {
          padding: {
            left: 20,
            right: 20,
            top: 0,
            bottom: 0
          }
        },
        maintainAspectRatio: false,
        tooltips: {
          backgroundColor: '#fff',
          titleFontColor: '#333',
          bodyFontColor: '#666',
          bodySpacing: 4,
          xPadding: 12,
          mode: "nearest",
          intersect: 0,
          position: "nearest"
        },
        legend: {
          position: "bottom",
          fillStyle: "#FFF",
          display: false
        },
        scales: {
          yAxes: [{
            ticks: {
              fontColor: "rgba(255,255,255,0.4)",
              fontStyle: "bold",
              beginAtZero: true,
              maxTicksLimit: 5,
              padding: 10
            },
            gridLines: {
              drawTicks: true,
              drawBorder: false,
              display: true,
              color: "rgba(255,255,255,0.1)",
              zeroLineColor: "transparent"
            }

          }],
          xAxes: [{
            gridLines: {
              zeroLineColor: "transparent",
              display: false,

            },
            ticks: {
              padding: 10,
              fontColor: "rgba(255,255,255,0.4)",
              fontStyle: "bold"
            }
          }]
        }
    }
}



