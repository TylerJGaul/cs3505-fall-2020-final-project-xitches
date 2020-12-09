import config as cfg

from boto3.session import Session

session = Session(aws_access_key_id=cfg.myconfig["AccessKey"],
                aws_secret_access_key=cfg.myconfig["Secret Access Key"])
                
s3 = session.resource('s3')

my_bucket = s3.Bucket('xitches')

for s3_files in my_bucket.objects.all():
    if "icon" in s3_files.key:
        s3.meta.client.download_file('xitches',s3_files.key,"icons/{}".format(s3_files.key))
    else:
        s3.meta.client.download_file('xitches',s3_files.key,s3_files.key)
