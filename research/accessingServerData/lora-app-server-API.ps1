# This block of code is only to handle our server
# which has a self-signed SSL certificate (temporarily)
# The code goes from line 4 to line 27
Add-Type @"
    using System;
    using System.Net;
    using System.Net.Security;
    using System.Security.Cryptography.X509Certificates;
    public class ServerCertificateValidationCallback
    {
        public static void Ignore()
        {
            ServicePointManager.ServerCertificateValidationCallback += 
                delegate
                (
                    Object obj, 
                    X509Certificate certificate, 
                    X509Chain chain, 
                    SslPolicyErrors errors
                )
                {
                    return true;
                };
        }
    }
"@
[ServerCertificateValidationCallback]::Ignore();

# Actual program code starts here
###########################################################

# Get user input for username, password
$username = Read-Host -Prompt 'Input username'
$password = Read-Host -Prompt 'Input password'

# Put the user credentials in a JSON object
#$creds = "{
# ""username"":""admin"",
# ""password"":""admin""
#}"

$creds = @{
 username=$username
 password=$password
}

$json = $creds | ConvertTo-Json

# Hard code the URI (URL) for the request (logging in/getting the JWT)
$uri = "https://10.118.0.93:8080/api/internal/login"

# Set the request header
$header = New-Object "System.Collections.Generic.Dictionary[[String],[String]]"
$header.Add("Accept", 'application/json')
# Finally, actually perform the POST and get the JWT token
$response = Invoke-RestMethod -Method Post -Uri $uri -ContentType 'application/json' -Headers $header -Body $json

$jwt = $response.jwt

Write-Host "This is your JWT: ", $jwt

#############################################################################
# Now fetch info on the application
$app_list_uri = "https://10.118.0.93:8080/api/applications"
$app_headers = New-Object "System.Collections.Generic.Dictionary[[String],[String]]"
$app_headers.Add("Accept", 'application/json')
$app_headers.Add("Grpc-Metadata-Authorization", $jwt)

$response = Invoke-RestMethod -Method Get -Uri $app_list_uri -ContentType 'application/json' -Headers $app_headers

$no_of_applications = $response.totalCount

Write-Host "There are", $no_of_applications, "applications."

#############################################################################
# Now fetch info on application with ID 1 (not sure how to get ID number yet)
$app_list_uri = "https://10.118.0.93:8080/api/applications/1"
$app_headers = New-Object "System.Collections.Generic.Dictionary[[String],[String]]"
$app_headers.Add("Accept", 'application/json')
$app_headers.Add("Grpc-Metadata-Authorization", $jwt)

$response = Invoke-RestMethod -Method Get -Uri $app_list_uri -ContentType 'application/json' -Headers $app_headers

$app_name = $response.name

Write-Host "Node name:", $app_name