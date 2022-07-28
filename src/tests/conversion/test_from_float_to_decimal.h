#ifndef SRC_TESTS_CONVERSION_TEST_FROM_FLOAT_TO_DECIMAL_H_
#define SRC_TESTS_CONVERSION_TEST_FROM_FLOAT_TO_DECIMAL_H_

static const float fails_big[] = {
    340282346638528859811704183484516925440.f,
    340282326356119256160033759537265639424.f,
    340282306073709652508363335590014353408.f,
    170141173319264429905852091742258462720.f,
    226854897759019239874469455656344616960.f,
    283568632339978851668922031544056414208.f,
    85070586659632214952926045871129231360.f,
    85070591730234615865843651857942052864.f,
    5316911666227013434557877866945576960.f,
    2658455991569831745807614120560689152.f,
    20769186196199271228741710417756160.f,
    10384593717069655257060992658440192.f,
    158456325028528675187087900672.0f,
    158456315583795709447797473280.0f,
    158456306139062743708507045888.0f,
    316912631167591418895594946560.f,
    158456325028528675187087900672.f,
    79228190848463234811415232512.f,
    79228181403730269072124805120.f,
    79228171958997303332834377728.f,
    79228162514264337593543950336.f,
    79228162514264337593543950335.f,
};

static const float fails_small[] = {
    0.00000000000000000000000000009999999429857660888699309391359540480357727713304344f,
    0.00000000000000000000000000009999998828004553267688105311366433422567940670147579f,
    0.00000000000000000000000000009999998226151445646676901231373326364778153626990814f,
    0.00000000000000000000000000009000000028539691658739462124217382784332763280814999f,
    0.00000000000000000000000000005000000015855384254855256735676323769073757378230555f,
    0.00000000000000000000000000004999999714928830444349654695679770240178863856652172f,
    4.999999414002276633844052655683216711283970335073789659219301029224880039691925048828125E-29f,
    1.2621774483536188886587657044524579674771302961744368076324462890625E-29f,
    1.0000000031710768509710513471352647538147514756461109453056224083411507308483123779296875E-29f,
    7.7037193183714626222678539700519994217126886949453196668630670929101000865557580254971981E-34f,
    4.8148245739821641389174087312824996385704304343408247917894169330688125540973487659357488E-35f,
    1.1754943508222875079687365372222456778186655567720875215087517062784172594547271728515625E-38f,
    1.4012984643248170709237295832899161312802619418765157717570682838897910826858606014866381E-45f,
};

static const float oks_big[] = {
    79228157791897854723898736640.0f,
    79228153069531371854253522944.0f,
    79228148347164888984608309248.0f,
    79228143624798406114963095552.0f,
    79228138902431923245317881856.0f,
    79228134180065440375672668160.0f,
    79228129457698957506027454464.0f,
    79228124735332474636382240768.0f,
    79228086956400611679220531200.0f,
    79228011398536885764897112064.0f,
    79227860282809433936250273792.0f,
    66023467187764787038071554048.0f,
    59421121885698253195157962752.0f,
    52818771861265236482599157760.0f,
    39614081257132168796771975168.0f,
    16505866796941196759517888512.0f,
    13204692965316309120649789440.0f,
    1031616674808824797469868032.0f,
    825293310332269320040611840.0f,
    4029752635971971865116672.0f,
    2417851639229258349412352.0f,
    2417851495114070273556480.0f,
    2417851350998882197700608.0f,
    3223801993485427031408640.0f,
    2014876317985985932558336.0f,
    1611900996742713515704320.0f,
    9444732965739290427392.0f,
    9444732402789337006080.0f,
    9444731839839383584768.0f,
    7870610617132757549056.0f,
    6296488268526224670720.0f,
    590295810358705651712.0f,
    590295775174333562880.0f,
    590295739989961474048.0f,
    491913163570797346816.0f,
    393530516782889041920.0f,
    147573952589676412928.0f,
    147573943793583390720.0f,
    147573934997490368512.0f,
    122978290892699336704.0f,
    98382629195722260480.0f,
    61489145446349668352.0f,
    36893488147419103232.0f,
    36893485948395847680.0f,
    36893483749372592128.0f,
    30744572723174834176.0f,
    27670116110564327424.0f,
    24595657298930565120.0f,
    8589934592.0f,
    8589934080.0f,
    8589933568.0f,
    7158278656.0f,
    6442450944.0f,
    5726622720.0f,
    5131067.5f,
    5131067.0f,
    5131066.5f,
    1131071.125f,
    1131071.0f,
    1131070.875f,
    131071.9921875f,
    131071.0078125f,
    131071.0f,
    131070.9921875f,
    109226.6640625f,
    98304.0078125f,
    98304.0f,
    98303.9921875f,
    87381.328125f,
    87381.0078125f,
    87381.0f,
    87380.9921875f,
    50000.00390625f,
    50000.0f,
    49999.99609375f,
    32000.001953125f,
    32000.0f,
    31999.998046875f,
    1024.0001220703125f,
    1024.0f,
    1023.99993896484375f,
    512.00006103515625f,
    512.0f,
    511.999969482421875f,
    511.99993896484375f,
    426.666656494140625f,
    384.0f,
    341.33331298828125f,
    64.00000762939453125f,
    64.0f,
    63.999996185302734375f,
    32.0f,
    31.9999980926513671875f,
    31.999996185302734375f,
    26.6666660308837890625f,
    24.0f,
    21.333332061767578125f,
    16.0000019073486328125f,
    16.0f,
    15.99999904632568359375f,
    10.98035526275634765625f,
    9.00000095367431640625f,
    9.0f,
    8.99999904632568359375f,
    8.0f,
    7.999999523162841796875f,
    6.666666507720947265625f,
    6.0f,
    5.33333301544189453125f,
    4.0f,
    3.9999997615814208984375f,
    3.999999523162841796875f,
    3.3333332538604736328125f,
    3.0f,
    2.666666507720947265625f,
    2.0000002384185791015625f,
    2.0f,
    1.99999988079071044921875f,
    1.50000011921f,
    1.5f,
    1.49999988079071044921875f,
    1.0f,
};

static const float oks_small[] = {
    0.15625f,
    0.999999940395355224609375f,
    0.24999998509883880615234375f,
    0.015624999068677425384521484375f,
    0.00006103515261202119290828704833984375f,
    9.31322519104327284367172978818416595458984375E-10f,
    2.1684042157240381566043314030822752869198666303418576717376708984375E-19f,
    1.08420210786201907830216570154113764345993331517092883586883544921875E-19f,
    5.42101053931009539151082850770568821729966657585464417934417724609375E-20f,
    1.3552526348275238478777071269264220543249166439636610448360443115234375E-20f,
    8.470328967672024049235669543290137839530729024772881530225276947021484375E-22f,
    3.308722252996884394232683415347710093566691025301906847744248807430267333984375E-24f,
    1.00974189849758434882589215556265566820272553262387293937507593000191263854503631591796875E-28f,
    4.038967593990337395303568622250622672810902130495491757500303720007650554180145263671875E-28f,
    6.462348150384539832485709795600996276497443408792786812000485952012240886688232421875E-27f,
    1.6543611264984421971163417076738550467833455126509534238721244037151336669921875E-24f,
    1.3333332538604736328125f,
    0.66666662693023681640625f,
    0.1666666567325592041015625f,
    0.01041666604578495025634765625f,
    0.0000406901017413474619388580322265625f,
    6.2088167940288485624478198587894439697265625E-10f,
    1.552204198507212140611954964697360992431640625E-10f,
    3.8805104962680303515298874117434024810791015625E-11f,
    2.4253190601675189697061796323396265506744384765625E-12f,
    9.473902578779370975414764188826666213572025299072265625E-15f,
    4.7369512893896854877073820944133331067860126495361328125E-15f,
    1.8503715974178458936356961306302082448382861912250518798828125E-17f,
    1.1564822483861536835223100816438801530239288695156574249267578125E-18f,
    1.445602810482692104402887602054850191279911086894571781158447265625E-19f,
    7.228014052413460522014438010274250956399555434472858905792236328125E-20f,
    3.6140070262067302610072190051371254781997777172364294528961181640625E-20f,
    9.03501756551682565251804751284281369549944429309107363224029541015625E-21f,
    5.64688597844801603282377969552675855968715268318192102015018463134765625E-22f,
    2.20581483533125626282178894356514006237779401686793789849616587162017822265625E-24f,
    5.514537088328140657054472358912850155944485042169844746240414679050445556640625E-25f,
    1.7232928401025439553295226121602656737326515756780764832001295872032642364501953125E-26f,
    4.30823210025635988832380653040066418433162893919519120800032396800816059112548828125E-27f,
    2.69264506266022493020237908150041511520726808699699450500020248000510036945343017578125E-28f,
    1.66666662693023681640625f,
    0.833333313465118408203125f,
    0.20833332836627960205078125f,
    0.013020833022892475128173828125f,
    0.00005086262899567373096942901611328125f,
    7.76102127009181685934890992939472198486328125E-10f,
    1.9402553175229542148372274823486804962158203125E-10f,
    4.85063829380738553709306870587170124053955078125E-11f,
    3.03164893362961596068316794116981327533721923828125E-12f,
    1.18423786469906873464186247701945831067860126495361328125E-14f,
    5.92118932349534367320931238509729155339300632476806640625E-15f,
    7.4014866543691795915116404813716144417412579059600830078125E-16f,
    2.31296457949036862234738765042862951304414309561252593994140625E-17f,
    1.44560286218148038896711728151789344565258943475782871246337890625E-18f,
    3.614007155453700972417793203794733614131473586894571781158447265625E-19f,
    1.8070035777268504862088966018973668070657367934472858905792236328125E-19f,
    9.0350178886342524310444830094868340353286839672364294528961181640625E-20f,
    4.51750894431712621552224150474341701766434198361821472644805908203125E-20f,
    1.1293772360792815538805603761858542544160854959045536816120147705078125E-20f,
    7.058607725495509711753502351161589090100534349403460510075092315673828125E-22f,
    2.757268642771683481153711855922495738320521230235726761748082935810089111328125E-24f,
    1.3786343213858417405768559279612478691602606151178633808740414679050445556640625E-24f,
    6.8931716069292087028842796398062393458013030755893169043702073395252227783203125E-25f,
    1.723292901732302175721069909951559836450325768897329226092551834881305694580078125E-25f,
    5.385290317913444299128343468598624488907268027804153831539224484004080295562744140625E-27f,
    3.365806448695902686955214667874140305567042517377596144712015302502550184726715087890625E-28f,
    0.75f,
    0.5f,
    0.1875f,
    0.125f,
    0.0625f,
    0.015625f,
    0.01171875f,
    0.0078125f,
    0.00390625f,
    0.000244140625f,
    0.0000457763671875f,
    0.000030517578125f,
    0.0000152587890625f,
    4.656612873077392578125E-10f,
    6.9849193096160888671875E-10f,
    1.08420217248550443400745280086994171142578125E-19f,
    0.100000001490116119384765625f,
    0.999000012874603271484375f,
    0.89999997615814208984375f,
    0.099899999797344207763671875f,
    0.009990000165998935699462890625f,
    0.000999000039882957935333251953125f,
    0.0000998999967123381793498992919921875f,
    0.0000099899998531327582895755767822265625f,
    9.990000080506433732807636260986328125E-7f,
    9.989999938397886580787599086761474609375E-8f,
    9.989999938397886580787599086761474609375E-9f,
    9.989999938397886580787599086761474609375E-10f,
    9.9899997996200085026430315338075160980224609375E-11f,
    9.99000014656470369800445041619241237640380859375E-12f,
    9.99000036340513819510533721768297255039215087890625E-13f,
    9.9900000923545950737292287158197723329067230224609375E-14f,
    9.15344799197644054533640201043453998863697052001953125E-15f,
    1.153448307063625563086139980129019022569991648197174072265625E-16f,
    1.15344827397640106096503298527267133977147750556468963623046875E-17f,
    1.15344825329688574713934111348745403802240616641938686370849609375E-18f,
    1.626303258728256651011179201304912567138671875E-19f,
    1.153448304995674031703570792950497292395084514282643795013427734375E-19f,
    1.153448272683931353850927243286095258412160546868108212947845458984375E-20f,
    7.1534482438357799764948774697004285627599529107101261615753173828125E-21f,
    7.153447436042213030178788728090377713186853725346736609935760498046875E-21f,
    7.534474876815749788050741124066818354965135995371383614838123321533203125E-22f,
    7.5344743719447704466031856605605365739819490045192651450634002685546875E-22f,
    7.5447452147130031849477575006039480054464974045913550071418285369873046875E-23f,
    7.54474458362427900813831317122109577921751366602620691992342472076416015625E-23f,
    9.5447507363792572275049173083396312523840609998160289251245558261871337890625E-24f,
    9.544749947518352006493111896611065969597831326609593816101551055908203125E-24f,
    5.44500023212807287423837444170905580415227575930003922621835954487323760986328125E-26f,
    5.444999615830490670322901463796114176975533827107511797294137068092823028564453125E-26f,
    1.44500012314726825099237640036909965964690392981051303422646014951169490814208984375E-26f,
    1.4449999690728727000135081558908642528527184467623811769954045303165912628173828125E-26f,
    1.50000004086780173371724926550248355418951443605857232199696227326057851314544677734375E-27f,
    1.4999999445713045143554566127035864249431485091534899112275525112636387348175048828125E-27f,
    1.45000001061659251011813649414606496360928751011842852136624060221947729587554931640625E-27f,
    1.449999914320095290756343841347167834362921583213346110596830840222537517547607421875E-27f,
    1.20000005195354083084615794296176626920088473422787433975145177100785076618194580078125E-27f,
    1.19999995565704361148436529016286913995451880732279192898204200901091098785400390625E-27f,
    1.15000002170233160724704517160534767862065780828773053912073009996674954891204833984375E-27f,
    1.1499999254058343878852525188064505493742918813826481283513203379698097705841064453125E-27f,
    1.1000000877476196030097250530478262172867968092526691492594181909225881099700927734375E-27f,
    1.09999999145112238364793240024892908804043088234758673849000842892564833164215087890625E-27f,
    1.0500000574964103794106122816914076267065698833125253486286965198814868927001953125E-27f,
    1.04999996119991316004881962889251049746020395640744293785928675788454711437225341796875E-27f,
    1.0000000272452011558114995103349890361263429573723815479979748488403856754302978515625E-27f,
    9.9999993094870393644970685753609190687997703046729913722856508684344589710235595703125E-28f,
    9.5000009329048915157417939177746757479248195833732015813666293979622423648834228515625E-28f,
    9.49999996993991932212386738978570445546116031432237747367253177799284458160400390625E-28f,
    9.0000006303927992797506662042104898421225503239717635750594126875512301921844482421875E-28f,
    8.999999667427827086132739676221518549658891054920939467365315067581832408905029296875E-28f,
    8.5000003278807070437595384906463039363202810645703255687521959771402180194854736328125E-28f,
    8.4999993649157348501416119626573326438566217955195014610580983571708202362060546875E-28f,
    8.0000000253686148077684107770821180305180118051688875624449792667292058467864990234375E-28f,
    7.99999954388612871095944751308763238428618217064347550859793045674450695514678955078125E-28f,
    7.50000020433900866858624632751241777094757218029286160998481136630289256572723388671875E-28f,
    7.4999997228565225717772830635179321247157425457674495561377625563181936740875244140625E-28f,
    7.00000038330940252940408187794271751137713255541683565752464346587657928466796875E-28f,
    6.99999990182691643259511861394823186514530292089142360367759465589188039302825927734375E-28f,
    6.500000080797310293412954164378531605574863296015397651217426755465567111968994140625E-28f,
    6.49999959931482419660399090038404595934303366148998559737037794548086822032928466796875E-28f,
    6.00000025976770415423078971480883134600442367113937169875725885503925383090972900390625E-28f,
    5.99999977828521805742182645081434569977259403661395964491021004505455493927001953125E-28f,
    5.5000004387380980150486252652391310864339840462633457462970909546129405498504638671875E-28f,
    5.49999995725561191823966200124464544020215441173793369245004214462824165821075439453125E-28f,
    5.0000001362260057790574975516749451806317147868619077399898742442019283771514892578125E-28f,
    4.99999965474351968224853428768045953439988515233649568614282543421722948551177978515625E-28f,
    4.50000031519639963987533310210524492106127516198588178752970634377561509609222412109375E-28f,
    4.4999998337139135430663698381107592748294455274604697336826575337909162044525146484375E-28f,
    4.00000001268430740388420538854105901525900590258444378122248963336460292339324951171875E-28f,
    3.999999771943064355479723756543816192143091085321737754298965228372253477573394775390625E-28f,
    3.500000432395944313106522570968601578804481094971123855685846137930639088153839111328125E-28f,
    3.500000191654701264702040938971358755688566277708417828762321732938289642333984375E-28f,
    3.499999950913458216297559306974115932572651460445711801838797327945940196514129638671875E-28f,
    3.49999971017221516789307767497687310945673664318300577491527292295359075069427490234375E-28f,
    3.000000129883852077115394857404415673002211835569685849378629427519626915454864501953125E-28f,
    2.999999889142609028710913225407172849886297018306979822455105022527277469635009765625E-28f,
    2.999999648401365980306431593409930026770382201044273795531580617534928023815155029296875E-28f,
    0.00000000000000000000000000025000003088542459379332304078347154134317722106936599f,
    0.00000000000000000000000000025000000681130028895287487758374725903158573934309539f,
    0.00000000000000000000000000024999998273717598411242671438402297671999425761682478f,
    0.00000000000000000000000000020000001267127752261443435102691509191874603599235749f,
    0.00000000000000000000000000020000000063421537019421026942705295076295029512922219f,
    0.00000000000000000000000000019999998859715321777398618782719080960715455426608689f,
    0.00000000000000000000000000015000001853125475627599382447008292480590633264161959f,
    0.00000000000000000000000000015000000649419260385576974287022078365011059177848429f,
    0.00000000000000000000000000014999999445713045143554566127035864249431485091534899f,
    0.00000000000000000000000000014999981390119816513218443727242652515737873796831947f,
    0.00000000000000000000000000010000001837270091372744125711331968711516875885931405f,
    0.00000000000000000000000000010000001235416983751732921631338861653727088842774640f,
    0.00000000000000000000000000010000000633563876130721717551345754595937301799617875f,
    0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f,
};

#endif  //  SRC_TESTS_CONVERSION_TEST_FROM_FLOAT_TO_DECIMAL_H_
