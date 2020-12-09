import config as cfg

from boto3.session import Session

session = Session(aws_access_key_id=cfg.myconfig["AccessKey"],
                aws_secret_access_key=cfg.myconfig["Secret Access Key"])
                
s3 = session.resource('s3')

# Our bucket on Amazon s3 that contains our csv files of our data
my_bucket = s3.Bucket('xitches')

for s3_files in my_bucket.objects.all():
    # If our file is an icon png then add it to a seperate folder named icons
    if "icon" in s3_files.key:
        s3.meta.client.download_file('xitches',s3_files.key,"icons/{}".format(s3_files.key))
    # Else download the file onto our current directory    
    else:
        s3.meta.client.download_file('xitches',s3_files.key,s3_files.key)
